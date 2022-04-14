#pragma once

namespace Todes
{
	class Particle;

	class IParticleForceGenerator
	{
	public:
		virtual ~IParticleForceGenerator() = default;

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		virtual void updateForce(Particle* particle) = 0;

	protected:
		explicit IParticleForceGenerator() = default;
	};

}

