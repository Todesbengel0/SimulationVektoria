#include "ParticleSpring.h"
#include "Particle.h"

namespace Todes
{
	ParticleSpring::ParticleSpring(Particle* other, const float& springConstant, const float& restLength)
		: ParticleSpringLike(springConstant, restLength),
		m_other(other)
	{
	}

	ParticleSpring::~ParticleSpring()
		= default;

	const Todes::Vector3D& ParticleSpring::getOtherEnd() const
	{
		return m_other->getPosition();
	}
}