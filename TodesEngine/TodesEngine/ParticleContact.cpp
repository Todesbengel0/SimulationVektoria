#include "ParticleContact.h"
#include "Common.h"
#include "Particle.h"

namespace Todes
{

	ParticleContact::ParticleContact()
		: m_particles{}
		, m_penetration(0.0f)
		, m_restitution(1.0f)
	{ }

	ParticleContact::ParticleContact(Particle* first, Particle* second, const Todes::Vector3D& contactNormal)
		: m_restitution(0.0f)
		, m_penetration(0.0f)
	{
		Init(first, second, contactNormal);
	}

	ParticleContact::~ParticleContact()
		= default;

	void ParticleContact::Init(Particle* first, Particle* second, const Todes::Vector3D& contactNormal)
	{
		if (first->hasFiniteMass())
		{
			m_particles[0] = first;
			m_particles[1] = second;
			m_contactNormal = contactNormal;
			return;
		}

		// If the first particle has infinite mass,
		// the particles are the wrong way around
		m_particles[0] = second;
		m_particles[1] = first;

		// We need to flip the contact normal
		m_contactNormal = -contactNormal;
	}

	float ParticleContact::CalculateSeparatingVelocity() const
	{
		// v_s = (a.veloyity - b.velocity) * (a.position - b.position).Norm 
		Vector3D relativeVelocity = m_particles[0]->getVelocity();
		if (m_particles[1]->hasFiniteMass())
			relativeVelocity -= m_particles[1]->getVelocity();

		return relativeVelocity * m_contactNormal;
	}

	std::pair<Vector3D, Vector3D> ParticleContact::resolve(const float& timeDelta)
	{
		if (!isResting(timeDelta))
			ResolveVelocity(timeDelta);

		if (m_penetration <= 0.0f) return std::pair<Vector3D, Vector3D>();

		return ResolveInterpenetration(timeDelta);
	}

	Particle* ParticleContact::getParticles()
	{
		return *m_particles;
	}

	const Vector3D& ParticleContact::getContactNormal() const
	{
		return m_contactNormal;
	}

	void ParticleContact::setRestitution(const float& restitution)
	{
		m_restitution = restitution;
	}

	const float& ParticleContact::getRestitution() const
	{
		return m_restitution;
	}

	void ParticleContact::setPenetration(const float& penetration)
	{
		m_penetration = penetration;
	}

	void ParticleContact::AddPenetration(const float& summand)
	{
		m_penetration += summand;
	}

	const float& ParticleContact::getPenetration() const
	{
		return m_penetration;
	}

	Particle* ParticleContact::getFirst() const
	{
		return m_particles[0];
	}

	Particle* ParticleContact::getSecond() const
	{
		return m_particles[1];
	}

	bool ParticleContact::isResting(const float& timeDelta)
	{
		// If both particles have infinite mass, there's nothing to resolve
		if (!m_particles[0]->hasFiniteMass()) return true;

		// We calculate the separating velocity
		// but save ourselves the single velocities
		const auto firstVelocity = m_particles[0]->getVelocity() * m_contactNormal;
		const auto secondVelocity = m_particles[1]->getVelocity() * m_contactNormal;
		float separatingVelocity = firstVelocity;
		if (m_particles[1]->hasFiniteMass())
			separatingVelocity -= secondVelocity;

		// Calculate velocity from Acceleration:
		// vfa = a.acceleration * timeDelta - b.acceleration * timeDelta
		// Multiply with contact normal to get the velocity towards the contact normal
		const auto firstAcceleration = m_particles[0]->getCurrentAcceleration() * m_contactNormal;
		const auto firstVelFromAcc = firstAcceleration * timeDelta;
		const auto secondAcceleration = m_particles[1]->getCurrentAcceleration() * m_contactNormal;
		const auto secondVelFromAcc = secondAcceleration * timeDelta;

		float velocityFromAcceleration = firstVelFromAcc;
		if (m_particles[1]->hasFiniteMass())
			velocityFromAcceleration -= secondVelFromAcc;

		// If we do not have any velocity from acceleration towards the contact,
		// this is not resting
		if (velocityFromAcceleration >= 0.0f) return false;

		// Now we need to check if the velocity created from the acceleration
		// is equal to the separation velocity
		// (in which case the whole velocity came from this resting contact)
		if (!nearlyEqual(velocityFromAcceleration, separatingVelocity)) return false;

		// In case of a resting contact, we do not have a separation velocity
		// But we need to remove the velocity that the contact prevents the particle to have

		// If we were to check the Acceleration again, we want it to be correct
		m_particles[0]->addCurrentAcceleration(-firstAcceleration * m_contactNormal);

		// We use the velocity that creates a lesser change to the velocity
		m_particles[0]->addVelocity(-std::max(firstVelocity, firstVelFromAcc) * m_contactNormal);

		if (m_particles[1]->hasFiniteMass())
		{
			// We do the same for the second particle
			m_particles[1]->addCurrentAcceleration(-secondAcceleration * m_contactNormal);
			m_particles[1]->addVelocity(-std::min(secondVelocity, secondVelFromAcc) * m_contactNormal);
		}

		return true;
	}

	void ParticleContact::ResolveVelocity(const float& timeDelta)
	{
		// We calculate the velocities of our particles
		// in direction of the contact normal
		const auto firstVelocityTowardsContact = m_particles[0]->getVelocity() * m_contactNormal;
		const auto secondVelocityTowardsContact = m_particles[1]->getVelocity() * m_contactNormal;

		// And get the separating Velocity
		auto separatingVelocity = firstVelocityTowardsContact;
		if (m_particles[1]->hasFiniteMass())
			separatingVelocity -= secondVelocityTowardsContact;

		// If the separating velocity is positive, the particles move away from each other
		if (separatingVelocity > 0.0f) return;

		// If the second particle has infinite mass, the velocity is turned around
		if (!m_particles[1]->hasFiniteMass())
		{
			// We need to use velocity of particle in contact direction
			// a.velocity += -a.velocity * c - a.velocity
			// <=> a.velocity += -a.velocity * (c + 1) 
			m_particles[0]->addVelocity((-firstVelocityTowardsContact * (m_restitution + 1.0f)) * m_contactNormal);
			return;
		}

		// Velocity changes depending on the mass of the particles
		const auto firstMass = m_particles[0]->getMass();
		const auto secondMass = m_particles[1]->getMass();

		// mass * velocity
		const auto mv1 = firstVelocityTowardsContact * firstMass;
		const auto mv2 = secondVelocityTowardsContact * secondMass;

		// 1 / (a.mass + b.mass)
		const auto inverseTotalMass = 1.0f / (firstMass + secondMass);

		// a.impulse = (mv1 - b.mass * a.velocity + 2 * mv2) / (a.mass + b.mass)
		const auto firstImpulse =
			(mv1 - secondMass * firstVelocityTowardsContact + 2 * mv2)
			* inverseTotalMass;

		// b.impulse = (2 * mv1 - a.mass * b.velocity + mv2) / (a.mass + b.mass)
		const auto secondImpulse =
			(2 * mv1 - firstMass * secondVelocityTowardsContact + mv2)
			* inverseTotalMass;

		// We calculate the new velocities after the impact
		
		// a.velocity += (a.impulse * restitution - a.velocityToContact) * m_contactNormal
		m_particles[0]->addVelocity(
			(firstImpulse * m_restitution - firstVelocityTowardsContact) * m_contactNormal);

		// b.velocity += (b.impulse * restitution - b.velocityToContact) * m_contactNormal
		m_particles[1]->addVelocity(
			(secondImpulse * m_restitution - secondVelocityTowardsContact) * m_contactNormal);
	}

	std::pair<Vector3D, Vector3D> ParticleContact::ResolveInterpenetration(const float& timeDelta)
	{
		// Particles Translation
		std::pair<Vector3D, Vector3D> particlesTranslation;

		// Without penetration, we do not need to resolve anything
		if (m_penetration <= 0.0001f) return particlesTranslation;

		// If both particles have infinite mass, there's nothing to resolve
		if (!m_particles[0]->hasFiniteMass()) return particlesTranslation;

		// Calculate d * n
		const auto penetrationVector = m_penetration * m_contactNormal;

		// If the second particle has infinite mass, we only move the first particle
		if (!m_particles[1]->hasFiniteMass())
		{
			particlesTranslation.first = penetrationVector;
			m_particles[0]->setPosition(m_particles[0]->getPosition() + penetrationVector);
			return particlesTranslation;
		}

		// Velocity change in accordance with their masses
		const auto firstMass = m_particles[0]->getMass();
		const auto secondMass = m_particles[1]->getMass();
		const auto totalMass = firstMass + secondMass;

		// Would be problematic to divide through 0
		if (totalMass <= 0.0f) return particlesTranslation;

		// Calculate (1 / (m_a + m_b)) * d * n
		const auto movePerMass = penetrationVector / totalMass;
		particlesTranslation.first = secondMass * movePerMass;
		particlesTranslation.second = -firstMass * movePerMass;

		// Resolve the interpenetration
		m_particles[0]->setPosition(m_particles[0]->getPosition() + particlesTranslation.first);
		m_particles[1]->setPosition(m_particles[1]->getPosition() + particlesTranslation.second);

		return particlesTranslation;
	}
	
}