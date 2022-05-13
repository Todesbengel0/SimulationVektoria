#pragma once
#include "ParticleLink.h"

namespace Todes
{
    /// <summary>
    /// Contact Generator that generates a contact if the two particles are too far apart.
    /// </summary>
    class ParticleCable : public ParticleLink
    {
	public:
		/// <summary>
		/// Particle Cable Constructor
		/// </summary>
		/// <param name="maxLength">The maximal length of the cable in [m].</param>
		/// <param name="restitution">The restitution coefficient of generated contacts [unitless quantity].</param>
		explicit ParticleCable(const float& maxLength = 1.0f, const float& restitution = 0.0f);
		~ParticleCable();

		/// <summary>
		/// Calculates the penetration between the two particles.
		/// </summary>
		float calculatePenetration() const override;

	protected:
		/// <summary>
		/// Returns the current Contact Normal
		/// </summary>
		Vector3D calculateContactNormal() const override;
    };

}