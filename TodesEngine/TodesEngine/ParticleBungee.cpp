#include "ParticleBungee.h"
#include "Vector3D.h"

Todes::ParticleBungee::ParticleBungee(Particle* other, const float& springConstant, const float& restLength)
	: ParticleSpring(other, springConstant, restLength)
{ }

Todes::ParticleBungee::~ParticleBungee()
= default;

float Todes::ParticleBungee::calculateMagnitude(const Vector3D& force) const
{
	auto magnitude = force.Length();

	if (magnitude <= m_restLength)
		return 0.0f;

	return m_springConstant * (m_restLength - magnitude);
}
