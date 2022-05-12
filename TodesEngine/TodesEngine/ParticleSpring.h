#pragma once
#include "ParticleSpringLike.h"

namespace Todes
{
	class Particle;

	/// <summary>
	/// A ParticleSpring is a particle force generator, which
	/// simulates a spring between two particles.
	/// </summary>
	class ParticleSpring : public ParticleSpringLike
	{
	public:
		/// <summary>
		/// ParticleSpring constructor.
		/// </summary>
		/// <param name="other">The reference position. Will not be influenced by the spring.</param>
		/// <param name="springConstant">The hardness of the spring.</param>
		/// <param name="restLength">The length at which no forces will be applied.</param>
		ParticleSpring(Particle* other, const float& springConstant, const float& restLength);
		~ParticleSpring();

	protected:
		const Vector3D& getOtherEnd() const override;

	protected:
		Particle* m_other;
	};
}

