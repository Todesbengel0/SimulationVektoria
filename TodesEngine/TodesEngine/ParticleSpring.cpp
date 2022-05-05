#include "ParticleSpring.h"
#include "Particle.h"

namespace Todes
{
	ParticleSpring::ParticleSpring(Particle* other, const float& springConstant, const float& restLength)
		: m_springConstant(springConstant),
		m_restLength(restLength),
		m_other(other)
	{
	}

	ParticleSpring::~ParticleSpring()
		= default;

	void ParticleSpring::updateForce(Particle* particle)
	{
		// Feather length
		auto force = particle->getPosition();
		force -= m_other->getPosition();

		// Force magnitude is needed for direction 
		auto magnitude = force.Length();

		if (magnitude == 0.0f)
			return;

		magnitude -= m_restLength;
		magnitude *= m_springConstant;

		// Resulting forces
		force.Normalize();
		force *= -magnitude;
		particle->addForce(force);
	}
}