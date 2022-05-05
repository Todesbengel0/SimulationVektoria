#pragma once
#include "IParticleForceGenerator.h"

namespace Todes
{
	class Particle;

	/// <summary>
	/// A ParticleSpring is a particle force generator, which
	/// simulates a spring between two particles.
	/// </summary>
	class ParticleSpring : public IParticleForceGenerator
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

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		void updateForce(Particle* particle) override;

	protected:
		Particle* m_other;
		const float m_springConstant;
		const float m_restLength;
	};
}

