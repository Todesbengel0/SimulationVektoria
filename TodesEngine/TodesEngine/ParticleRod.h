#pragma once
#include "ParticleLink.h"

namespace Todes
{
	class ParticleContact;

	/// <summary>
	/// Creates a distance constraint between two particles.
	/// A contact gets created if this constraint is not fulfilled.
	/// </summary>
	class ParticleRod : public ParticleLink
	{
	public:
		/// <summary>
		/// Particle Rod Constructor
		/// </summary>
		/// <param name="maxLength">The length of the rod in [m].</param>
		explicit ParticleRod(const float& length = 1.0f);
		~ParticleRod();

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