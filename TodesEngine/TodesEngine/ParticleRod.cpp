#include "ParticleRod.h"
#include "ParticleLink.h"
#include "Particle.h"

namespace Todes
{

	ParticleRod::ParticleRod(const float& length /*= 1.0f*/)
		: ParticleLink(length, 0.0f)
	{ }

	ParticleRod::~ParticleRod()
		= default;

	float ParticleRod::calculatePenetration() const
	{
		return std::abs(m_triggerDistance - currentLength());
	}

	Vector3D ParticleRod::calculateContactNormal() const
	{
		// We need the contact normal, if we want to push the particles away from each other
		// <=> if the current length is smaller than the trigger distance
		if (currentLength() <= m_triggerDistance)
			return (m_particles[0]->getPosition() - m_particles[1]->getPosition()).Normalize();

		// We need the negative contact normal, if we want to pull the particles together
		// <=> if the current length is greater than the trigger distance
		return (m_particles[1]->getPosition() - m_particles[0]->getPosition()).Normalize();
	}

}