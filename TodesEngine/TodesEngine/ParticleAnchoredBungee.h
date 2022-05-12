#pragma once
#include "ParticleAnchoredSpring.h"

namespace Todes
{

	class ParticleAnchoredBungee : public ParticleAnchoredSpring
	{
	public:
		ParticleAnchoredBungee(const Vector3D& anchor, const float& springConstant, const float& restLength);
		~ParticleAnchoredBungee();

	protected:
		float calculateMagnitude(const Vector3D& force) const override;
	};

}