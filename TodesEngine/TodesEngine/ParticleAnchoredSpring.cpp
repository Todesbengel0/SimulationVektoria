#include "ParticleAnchoredSpring.h"
#include "Particle.h"
#include "Vector3D.h"

namespace Todes
{
	ParticleAnchoredSpring::ParticleAnchoredSpring(const Vector3D& anchor, const float& springConstant, const float& restLength)
		: ParticleSpringLike(springConstant, restLength),
		m_anchor(anchor)
	{
	}

	ParticleAnchoredSpring::~ParticleAnchoredSpring()
		= default;

	void ParticleAnchoredSpring::setOtherEnd(const Vector3D& anchor)
	{
		m_anchor = anchor;
	}

	const Vector3D& ParticleAnchoredSpring::getOtherEnd() const
	{
		return m_anchor;
	}
}