#pragma once
#include "IParticleForceGenerator.h"
#include "Vector3D.h"

namespace Todes
{
	class Particle;

	/// <summary>
	/// ParticleAnchoredSpring is a particle generator, which
	/// simulates a spring, which is anchored to a specific point.
	/// </summary>
	class ParticleAnchoredSpring : public IParticleForceGenerator
	{
	public:
		/// <summary>
		/// ParticleAnchoredSpring constructor
		/// </summary>
		/// <param name="anchor">An immovable end of the spring</param>
		/// <param name="springConstant">Defines the hardness of the spring</param>
		/// <param name="restLength">The length at which no forces are applied</param>
		explicit ParticleAnchoredSpring(const Vector3D& anchor, const float& springConstant, const float& restLength);
		~ParticleAnchoredSpring();

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		void updateForce(Particle* particle) override;

	protected:
		Vector3D m_anchor;
		const float m_springConstant;
		const float m_restLength;
	};

}