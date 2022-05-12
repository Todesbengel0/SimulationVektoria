#include "ParticleAnchoredBungee.h"

Todes::ParticleAnchoredBungee::ParticleAnchoredBungee(const Vector3D& anchor, const float& springConstant, const float& restLength)
	: ParticleAnchoredSpring(anchor, springConstant, restLength)
{ }

Todes::ParticleAnchoredBungee::~ParticleAnchoredBungee()
= default;

float Todes::ParticleAnchoredBungee::calculateMagnitude(const Vector3D& force) const
{
	auto magnitude = force.Length();

	if (magnitude <= m_restLength)
		return 0.0f;

	return m_springConstant * (m_restLength - magnitude);
}