#include "ParticleContact.h"
#include "Particle.h"
#define nearlyEqual(a, b)	float(a - b) < 0.01f && float(a - b) > -0.01f

namespace Todes
{

	ParticleContact::ParticleContact()
		= default;

	ParticleContact::ParticleContact(Particle* first, Particle* second)
		: m_restitution(0.0f)
		, m_penetration(0.0f)
	{
		m_particles[0] = first;
		m_particles[1] = second;
	}

	ParticleContact::~ParticleContact()
		= default;

	void ParticleContact::Init(Particle* first, Particle* second)
	{
		m_particles[0] = first;
		m_particles[1] = second;
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
		ResolveVelocity(timeDelta);
		return ResolveInterpenetration(timeDelta);
	}

	Particle* ParticleContact::getParticles()
	{
		return *m_particles;
	}

	void ParticleContact::setContactNormal(const Vector3D& normal)
	{
		m_contactNormal = normal;
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

	void ParticleContact::ResolveVelocity(const float& timeDelta)
	{
		// Checks if the particles are the wrong way around
		if (!m_particles[0]->hasFiniteMass())
		{
			// If both particles have infinite mass, there's nothing to resolve
			if (!m_particles[1]->hasFiniteMass()) return;

			auto temp = m_particles[0];

			m_particles[0] = m_particles[1];
			m_particles[1] = temp;
			m_contactNormal *= -1;
		}

		float separatingVelocity = CalculateSeparatingVelocity();

		// If the separating velocity is positive, the particles move away from each other
		if (separatingVelocity > 0.0f) return;

#pragma region Calculation_for_resting_contacts
		// Calculation for resting contacts

		// Acceleration is always 0 in Rumble3D

		// Calculate velocity from Acceleration: vfa = a.acceleration * timeDelta - b.acceleration * timeDelta
		Vector3D separatingAcceleration = m_particles[0]->getAcceleration();
		if (m_particles[1]->hasFiniteMass())
			separatingAcceleration -= m_particles[1]->getAcceleration();

		// Velocity = Acceleration * Time
		auto velocityFromAcceleration = separatingAcceleration * timeDelta;

		// Check how much velocity works towards contact normal
		auto velocityTowardsNormal = velocityFromAcceleration * m_contactNormal;

		// Now we need to check if the velocity created from the acceleration
		// is equal to the separation velocity
		// (in which case the whole velocity came from this resting contact)
		if (nearlyEqual(velocityTowardsNormal, separatingVelocity))
		{
			// In case of a resting contact, we do not have a separation velocity
			// But we need to remove the velocity that the contact prevents the particle to have
			m_particles[0]->addVelocity(-velocityFromAcceleration);

			// Because the two particles are not supposed to be colliding anymore,
			// we need to return from this function
			return;
		}

		// If we actually have a separation velocity (negative) from the acceleration
		// (even though it is not the only velocity working in this direction)
		// we have to at least remove the part it plays
		if (velocityTowardsNormal < 0.0f)
			separatingVelocity -= velocityTowardsNormal;

#pragma endregion

		// Restitution Velocity vs' = -c * vs
		float restitutionVelocity = -m_restitution * separatingVelocity;

		// If the second particle has infinite mass, the velocity is turned around
		if (!m_particles[1]->hasFiniteMass())
		{
			// Should use velocity of particle in contact direction, I think
			m_particles[0]->addVelocity(2.0f * restitutionVelocity * m_contactNormal);
			return;
		}

		// Velocity changes depending on the mass of the particles
		auto totalMass = m_particles[0]->getMass() + m_particles[1]->getMass();

		// Impulse g = (m1 + m2) * vs'
		const auto impulse = totalMass * restitutionVelocity;

		// a.velocity' = a.velocity + m_contactNormal * g / a.mass
		m_particles[0]->addVelocity(m_contactNormal * impulse * m_particles[0]->getInverseMass());

		// For the second particle we have the new velocity towards the negative contact normal
		// = b.velocity - m_contactNormal * g / b.mass
		m_particles[1]->addVelocity(-m_contactNormal * impulse * m_particles[1]->getInverseMass());
	}

	std::pair<Vector3D, Vector3D> ParticleContact::ResolveInterpenetration(const float& timeDelta)
	{
		// Particles Translation
		std::pair<Vector3D, Vector3D> particlesTranslation;

		// Without penetration, we do not need to resolve anything
		if (m_penetration <= 0) return particlesTranslation;

		// If both particles have infinite mass, there's nothing to resolve
		if (!m_particles[0]->hasFiniteMass() && !m_particles[1]->hasFiniteMass()) return particlesTranslation;

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
		const auto movePerMass = (1.0f / totalMass) * penetrationVector;
		particlesTranslation.first = firstMass * movePerMass;
		particlesTranslation.second = -secondMass * movePerMass;

		// Resolve the interpenetration
		m_particles[0]->setPosition(m_particles[0]->getPosition() + particlesTranslation.first);
		m_particles[1]->setPosition(m_particles[1]->getPosition() + particlesTranslation.second);

		return particlesTranslation;
	}
	
}