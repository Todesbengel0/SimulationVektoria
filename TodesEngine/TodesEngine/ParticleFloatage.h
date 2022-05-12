#pragma once
#include "IParticleForceGenerator.h"

namespace Todes
{
	/// <summary>
	/// Force Generator for a particle swimming in/on water
	/// </summary>
	class ParticleFloatage : public IParticleForceGenerator
	{
	public:
		/// <summary>
		/// ParticleFloatige Constructor.
		/// </summary>
		/// <param name="maxDepth">Depth in [m] at which the body is completely submerged.</param>
		/// <param name="volume">Volume of the body in [m^3].</param>
		/// <param name="liquidHeight">Height of the liquid in [m].</param>
		/// <param name="liquidDensity">Density of the volume in [kg/m^3].</param>
		/// <param name="gravity">Gravity in [m/s] working on the particle.</param>
		explicit ParticleFloatage
		(
			const float& maxDepth,
			const float& volume,
			const float& liquidHeight,
			const float& liquidDensity = 1000.0f,
			const float& gravity = 9.807f
		);
		~ParticleFloatage();

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		void updateForce(Particle* particle) override;

		/// <summary>
		/// Returns the current at which the body is completely submerged.
		/// </summary>
		float getMaxDepth() const;

		/// <summary>
		/// Sets the current at which the body is completely submerged.
		/// </summary>
		/// <param name="depth">Depth in [m] at which the body is completely submerged.</param>
		void setMaxDepth(const float& depth);

		/// <summary>
		/// Returns the volume of the body.
		/// </summary>
		float getVolume() const;

		/// <summary>
		/// Sets the volume of the body.
		/// </summary>
		/// <param name="volume">Volume of the body in [m^3].</param>
		void setVolume(const float& volume);

		/// <summary>
		/// Returns the height of the liquid.
		/// </summary>
		float getLiquidHeight() const;

		/// <summary>
		/// Sets the height of the liquid.
		/// </summary>
		/// <param name="height">Height of the liquid in [m].</param>
		void setLiquidHeight(const float& height);

		/// <summary>
		/// Returns the liquid density.
		/// </summary>
		float getLiquidDensity() const;

		/// <summary>
		/// Sets the liquid density.
		/// </summary>
		/// <param name="density">Density of the volume in [kg/m^3].</param>
		void setLiquidDensity(const float& density);

		/// <summary>
		/// Returns the gravity (up-force) working on the particle.
		/// </summary>
		float getGravity() const;

		/// <summary>
		/// Sets the gravity (up-force) of this generator.
		/// </summary>
		/// <param name="gravity">Gravity in [m/s] working on the particle.</param>
		void setGravity(const float& gravity);

	protected:
		float m_maxDepth;
		float m_volume;
		float m_liquidHeight;
		float m_liquidDensity;

		float m_gravity;
	};

}