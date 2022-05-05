#include "ParticleAnchoredSpring.h"
#include "Particle.h"
#include "Vector3D.h"

namespace Todes
{
	ParticleAnchoredSpring::ParticleAnchoredSpring(const Vector3D& anchor, const float& springConstant, const float& restLength)
		: m_anchor(anchor),
		m_springConstant(springConstant),
		m_restLength(restLength)
	{
	}

	ParticleAnchoredSpring::~ParticleAnchoredSpring()
		= default;

	void ParticleAnchoredSpring::updateForce(Particle* particle)
	{
		auto force = particle->getPosition();
		force -= m_anchor;

		auto magnitude = force.Length();

		if (magnitude == 0.0f)
			return;

		magnitude -= m_restLength;
		magnitude *= m_springConstant;

		force.Normalize();
		force *= -magnitude;
		particle->addForce(force);
	}
}