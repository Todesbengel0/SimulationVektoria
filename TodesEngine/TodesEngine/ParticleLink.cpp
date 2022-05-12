#include "ParticleLink.h"
#include "Particle.h"
#include "ParticleContact.h"

namespace Todes
{
	ParticleLink::ParticleLink()
		= default;

	ParticleLink::~ParticleLink()
		= default;

	void ParticleLink::setParticles(Particle* first, Particle* second)
	{
		m_particles[0] = first;
		m_particles[1] = second;
	}

	Particle* ParticleLink::getFirst() const
	{
		return m_particles[0];
	}

	Particle* ParticleLink::getSecond() const
	{
		return m_particles[1];
	}

	float Todes::ParticleLink::currentLength() const
	{
		assert(m_particles[0] && m_particles[1]);

		const auto distance = m_particles[0]->getPosition() - m_particles[1]->getPosition();
		return distance.Length();
	}
}