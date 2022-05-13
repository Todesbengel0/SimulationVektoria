#include "ParticleWorld.h"
#include "Particle.h"
#include "ParticleEngineCI.h"
#include "ParticleContact.h"
#include "IParticleContactGenerator.hpp"
#include "ParticleContactResolver.h"

#include <algorithm>

namespace Todes
{
	ParticleWorld::ParticleWorld(const unsigned int& maxContacts)
		: m_contactContainer(maxContacts)
	{ }

	ParticleWorld::~ParticleWorld()
		= default;

	ParticleForceRegistry& ParticleWorld::getParticleForceRegistry()
	{
		return m_forceRegistry;
	}

	const ParticleForceRegistry& ParticleWorld::getParticleForceRegistry() const
	{
		return m_forceRegistry;
	}

	Todes::ParticleContactRegistry& ParticleWorld::getParticleContactRegistry()
	{
		return m_contactRegistry;
	}

	const Todes::ParticleContactRegistry& ParticleWorld::getParticleContactRegistry() const
	{
		return m_contactRegistry;
	}

	std::vector<Particle*>& ParticleWorld::getParticles()
	{
		return m_particles;
	}

	const std::vector<Particle*>& ParticleWorld::getParticles() const
	{
		return m_particles;
	}

	void ParticleWorld::addParticle(Particle* particle)
	{
		m_particles.push_back(particle);
	}

	bool ParticleWorld::removeParticle(Particle* particle)
	{
		const auto removableParticle = std::remove(m_particles.begin(), m_particles.end(), particle);

		if (removableParticle == m_particles.end())
			return false;

		m_particles.erase(removableParticle);
		return true;
	}

	void ParticleWorld::updateForces()
	{
		m_forceRegistry.updateForces();
	}

	void ParticleWorld::integrate(const float& timeDelta)
	{
		for (int i = 0; i < m_particles.size(); ++i)
			m_particles[i]->integrate(timeDelta);
	}

	void ParticleWorld::updateCollisions()
	{
		for (const auto& generator : m_contactRegistry)
		{
			if (m_contactContainer.isFull()) return;

			generator->addContact(m_contactContainer);
		}
	}

	void ParticleWorld::solveCollisions(const float& timeDelta)
	{
		const auto usedContacts = m_contactContainer.getUsedEntries();

		if (usedContacts > 0)
			ParticleContactResolver::ResolveContacts(m_contactContainer, usedContacts * 2, timeDelta);

		reset();
	}

	void ParticleWorld::updateWorld(const float& timeDelta)
	{
		// It's important to first update the Forces and then check for collisions
		
		// Updates the Forces of the Particles
		updateForces();

		// Integrates the Particles
		integrate(timeDelta);

		// Update Collisions
		updateCollisions();

		// Solves Collisions
		solveCollisions(timeDelta);
	}

	void ParticleWorld::reset()
	{
		m_contactContainer.reset();
	}

}