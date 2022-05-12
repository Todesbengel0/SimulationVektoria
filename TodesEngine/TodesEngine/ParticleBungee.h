#pragma once
#include "ParticleSpring.h"

namespace Todes
{

	class ParticleBungee : public ParticleSpring
	{
	public:
		ParticleBungee(Particle* other, const float& springConstant, const float& restLength);
		~ParticleBungee();

	protected:
		float calculateMagnitude(const Vector3D& force) const override;
	};

}