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
		/// <param name="particleRadius">Radius of the particle in [m].</param>
		/// <param name="liquidHeight">Height of the liquid in [m].</param>
		/// <param name="liquidDensity">Density of the volume in [kg/m^3].</param>
		/// <param name="liquidViscosity">Viscosity of the liquid in [Pa*s]</param>
		/// <param name="impactConservation">Factor of Velocity that is kept during impact in [%].</param>
		/// <param name="gravity">Gravity in [m/s] working on the particle.</param>
		explicit ParticleFloatage
		(
			const float& particleRadius,
			const float& liquidHeight,
			const float& impactConservation = 0.7f,
			const float& liquidDensity = 1000.0f,
			const float& liquidViscosity = 0.0010518f,
			const float& gravity = 9.807f
		);
		~ParticleFloatage();

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		void updateForce(Particle* particle) override;

		/// <summary>
		/// Returns the radius of the particle.
		/// </summary>
		const float& getRadius() const;

		/// <summary>
		/// Sets the radius of the particle.
		/// </summary>
		/// <param name="volume">Radius of the particle in [m].</param>
		void setRadius(const float& radius);

		/// <summary>
		/// Returns the height of the liquid.
		/// </summary>
		const float& getLiquidHeight() const;

		/// <summary>
		/// Sets the height of the liquid.
		/// </summary>
		/// <param name="height">Height of the liquid in [m].</param>
		void setLiquidHeight(const float& height);

		/// <summary>
		/// Returns the liquid density.
		/// </summary>
		const float& getLiquidDensity() const;

		/// <summary>
		/// Sets the liquid density.
		/// </summary>
		/// <param name="density">Density of the volume in [kg/m^3].</param>
		void setLiquidDensity(const float& density);

		/// <summary>
		/// Returns the liquid viscosity.
		/// </summary>
		const float& getLiquidViscosity() const;

		/// <summary>
		/// Sets the liquid viscosity.
		/// </summary>
		/// <param name="viscosity">Viscosity of the liquid in [Pa*s]</param>
		void setLiquidViscosity(const float& viscosity);

		/// <summary>
		/// Returns the impact conservation factor.
		/// </summary>
		const float& getImpactConservation() const;

		/// <summary>
		/// Sets the impact conservation factor.
		/// </summary>
		/// <param name="conservation">Factor of Velocity that is kept during impact in [%].</param>
		void setImpactConservation(const float& conservation);

		/// <summary>
		/// Returns the gravity (up-force) working on the particle.
		/// </summary>
		const float& getGravity() const;

		/// <summary>
		/// Sets the gravity (up-force) of this generator.
		/// </summary>
		/// <param name="gravity">Gravity in [m/s] working on the particle.</param>
		void setGravity(const float& gravity);

	protected:
		float m_radius;
		float m_liquidHeight;
		float m_liquidDensity;
		float m_liquidViscosity;
		float m_impactConservation;

		float m_gravity;

		bool m_impacted;
	};

}