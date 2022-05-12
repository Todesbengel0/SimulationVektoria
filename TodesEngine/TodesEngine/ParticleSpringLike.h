#pragma once
#include "IParticleForceGenerator.h"

namespace Todes
{
	class Vector3D;

	class ParticleSpringLike : public IParticleForceGenerator
	{
	public:
		/// <summary>
		/// ParticleSpringLike constructor.
		/// </summary>
		/// <param name="springConstant">The hardness of the spring.</param>
		/// <param name="restLength">The length at which no forces will be applied.</param>
		ParticleSpringLike(const float& springConstant, const float& restLength);
		~ParticleSpringLike() = default;

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		void updateForce(Particle* particle) override;

	protected:
		virtual const Vector3D& getOtherEnd() const = 0;
		virtual float calculateMagnitude(const Vector3D& force) const;

	protected:
		const float m_springConstant;
		const float m_restLength;
	};

}

