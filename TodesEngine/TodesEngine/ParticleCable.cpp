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

	Vector3D ParticleCable::calculateContactNormal() const
	{		
		// Contact normal n = (a.position - b.positon).Norm
		// but we need it the other way around, because we want to pull pack to the other particle
		auto normal = m_particles[1]->getPosition() - m_particles[0]->getPosition();
		normal.Normalize();
		return normal;
	}

}