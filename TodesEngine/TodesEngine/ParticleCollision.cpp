#include "ParticleCollision.h"


namespace Todes
{
	ParticleCollision::ParticleCollision(const float& minDistance /*= 1.0f*/, const float& restitution /*= 0.0f*/)
		: ParticleLink(minDistance, restitution)
	{ }

	ParticleCollision::ParticleCollision(Particle* first, Particle* second, const float& minDistance /*= 1.0f*/, const float& restitution /*= 0.0f*/)
		: ParticleLink(minDistance, restitution)
	{
		ParticleLink::setParticles(first, second);
	}

	ParticleCollision::~ParticleCollision()
		= default;

	float ParticleCollision::calculatePenetration() const
	{
		return m_triggerDistance - currentLength();
	}
}