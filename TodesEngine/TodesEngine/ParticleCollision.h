#pragma once
#include "ParticleLink.h"

namespace Todes
{
    class ParticleCollision : public ParticleLink
    {
	public:
		/// <summary>
		/// Particle Collision Constructor
		/// </summary>
		/// <param name="minDistance">The minimal distance the particle need to stay away from each other in [m].</param>
		/// <param name="restitution">The restitution coefficient of generated contacts [unitless quantity].</param>
		explicit ParticleCollision(const float& minDistance = 1.0f, const float& restitution = 0.0f);
		explicit ParticleCollision(Particle* first, Particle* second, const float& minDistance = 1.0f, const float& restitution = 0.0f);
		~ParticleCollision();

		/// <summary>
		/// Calculates the penetration between the two particles.
		/// </summary>
		float calculatePenetration() const override;
    };

}