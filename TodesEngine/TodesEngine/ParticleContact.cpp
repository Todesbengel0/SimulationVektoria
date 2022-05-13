#include "ParticleContact.h"
#include "Particle.h"

namespace Todes
{

	ParticleContact::ParticleContact()
		= default;

	ParticleContact::ParticleContact(Particle* first, Particle* second)
		: m_restitution(0.0f)
		, m_penetration(0.0f)
		, m_particlesMovement{}
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
		// v_s = (\dot{p_a} - \dot{p_b}) * (\hat{p_a -p_b})
		Vector3D relativeVelocity = m_particles[0]->getVelocity();
		if (m_particles[1]->hasFiniteMass())
			relativeVelocity -= m_particles[1]->getVelocity();

		return relativeVelocity * m_contactNormal;
	}

	void ParticleContact::resolve(const float& timeDelta)
	{
		ResolveVelocity(timeDelta);
		ResolveInterpenetration(timeDelta);
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

	const Vector3D* ParticleContact::getParticlesMovement() const
	{
		return m_particlesMovement;
	}

	void ParticleContact::ResolveVelocity(const float& timeDelta)
	{
		const float separatingVelocity = CalculateSeparatingVelocity();

		// If particles don't move, there's nothing to resolve
		if (separatingVelocity > 0.0f) return;

		// If both particles have infinite mass, there's nothing to resolve
		if (!m_particles[0]->hasFiniteMass() && !m_particles[1]->hasFiniteMass()) return;

		// \prime{v_s} = -c*v_s
		float newSeparatingVelocity = -separatingVelocity * m_restitution;

		// Calculation for resting contacts
		Vector3D accelerationCausedVelocity = m_particles[0]->getAcceleration();
		if (m_particles[1]->hasFiniteMass())
			accelerationCausedVelocity -= m_particles[1]->getAcceleration();

		// Check how much acceleration works towards contact normal
		auto causedSeparationVelocity = accelerationCausedVelocity * m_contactNormal;

		// If we have a collision velocity, it needs to be subtracted from newSeperationVelocity
		if (causedSeparationVelocity < 0.0f)
		{
			newSeparatingVelocity += m_restitution * causedSeparationVelocity;
			if (newSeparatingVelocity < 0.0f)
				newSeparatingVelocity = 0.0f;
		}

		// Total Velocity
		const auto deltaVelocity = newSeparatingVelocity - separatingVelocity;

		// Velocity changes depending on the mass of the particles
//		auto totalMass = m_particles[0]->getMass();
		auto totalInverseMass = m_particles[0]->getInverseMass();
		if (m_particles[1]->hasFiniteMass())
//			totalMass += m_particles[1]->getMass();
			totalInverseMass += m_particles[1]->getInverseMass();

		// Total impulse g = (m_1 + m_2) * v 
//		const auto impulse = deltaVelocity * totalMass;
		const auto impulse = deltaVelocity / totalInverseMass;

		// Impulse * Mass in direction of contact normal
		const auto impulsePerMass = m_contactNormal * impulse;

		// \prime{\hat{p}} = \dot{p} + 1/m * g	
		if (m_particles[0]->hasFiniteMass())
			m_particles[0]->setVelocity(
				m_particles[0]->getVelocity() +
				impulsePerMass * m_particles[0]->getInverseMass());

		// Negative, because we look at particle 0
		if (m_particles[1]->hasFiniteMass())
			m_particles[1]->setVelocity(m_particles[1]->getVelocity() +
				impulsePerMass * -m_particles[1]->getInverseMass());
	}

	void ParticleContact::ResolveInterpenetration(const float& timeDelta)
	{
		// Without penetration, we do not need to resolve anything
		if (m_penetration <= 0) return;

		// Velocity change in accordance with their masses
//		auto totalMass = m_particles[0]->getMass();
		auto totalInverseMass = m_particles[0]->getInverseMass();
		if (m_particles[1]->hasFiniteMass())
//			totalMass += m_particles[1]->getMass();
			totalInverseMass += m_particles[1]->getInverseMass();
		
//		if (totalMass <= 0.0f) return;
		if (totalInverseMass <= 0) return;

		// Calculate (m_a + m_b) * d * n
//		auto movePerMass = m_contactNormal * m_penetration * totalMass;
		auto movePerInverseMass = m_contactNormal * (m_penetration / totalInverseMass);

		// Calculate Delta-p_a and Delta-p_b
//		m_particlesMovement[0] = movePerMass * m_particles[0]->getInverseMass();
		m_particlesMovement[0] = movePerInverseMass * m_particles[0]->getInverseMass();
		if (m_particles[1]->hasFiniteMass())
//			m_particlesMovement[1] = movePerMass * -m_particles[1]->getInverseMass();
			m_particlesMovement[1] = movePerInverseMass * -m_particles[1]->getInverseMass();

		else
			m_particlesMovement[1] = Vector3D();

		// Resolve the interpenetration
		m_particles[0]->setPosition(m_particles[0]->getPosition() + m_particlesMovement[0]);
		if (m_particles[1]->hasFiniteMass())
			m_particles[1]->setPosition(m_particles[1]->getPosition() + m_particlesMovement[1]);
	}
	
}