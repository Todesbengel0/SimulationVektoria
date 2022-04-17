#pragma once
#include "IParticleForceGenerator.h"
#include "Vector3D.h"

namespace Todes
{
#pragma once
	class Particle;
	
	/// <summary>
	/// A ParticleGravity is a particle force generator, which
	/// applies a constant given force to particles.
	/// </summary>
	class ParticleGravityForce : public IParticleForceGenerator
	{
	public:
		/**
			* \brief ParticleGravity constructor
			* \param gravity A constant force
			*/
		
		/// <summary>
		/// ParticleGravityForce constructor
		/// </summary>
		/// <param name="gravity">A constant force</param>
		explicit ParticleGravityForce(const Vector3D& gravity);
		~ParticleGravityForce();

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		void updateForce(Particle* particle) override;

		/// <summary>
		/// Returns the current gravity.
		/// </summary>
		const Vector3D& getGravity() const;

		/// <summary>
		/// Set the current gravity.
		/// </summary>
		void setGravity(const Vector3D& gravity);

	protected:
		Vector3D m_gravity;
	};
}