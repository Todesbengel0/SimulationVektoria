#pragma once
#include "ParticleSpringLike.h"
#include "Vector3D.h"

namespace Todes
{
	class Particle;

	/// <summary>
	/// ParticleAnchoredSpring is a particle generator, which
	/// simulates a spring, which is anchored to a specific point.
	/// </summary>
	class ParticleAnchoredSpring : public ParticleSpringLike
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

		void setOtherEnd(const Vector3D& anchor);

		const Vector3D& getOtherEnd() const override;

	protected:
		Vector3D m_anchor;
	};

}