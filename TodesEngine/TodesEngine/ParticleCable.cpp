#include "ParticleCable.h"
#include "Particle.h"
#include "ParticleContact.h"

namespace Todes
{
	ParticleCable::ParticleCable(const float& maxLength /*= 1.0f*/, const float& restitution /*= 0.0f*/)
		: ParticleLink(maxLength, restitution)
	{ }

	ParticleCable::~ParticleCable()
		= default;

	float ParticleCable::calculatePenetration() const
	{
		return currentLength() - m_triggerDistance;
	}
}