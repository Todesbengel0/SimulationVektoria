#include "ParticleWorld.h"
#include "Particle.h"
#include "ParticleEngineCI.h"

#include <algorithm>

namespace Todes
{
	ParticleWorld::ParticleWorld()
		= default;

	ParticleWorld::~ParticleWorld()
		= default;

	void ParticleWorld::setComputationInterface(ParticleEngineCI* computationInterface)
	{
		m_computationInterface = computationInterface;
	}

	IComputationInterface* ParticleWorld::getComputationInterface() const
	{
		return m_computationInterface;
	}

	ParticleForceRegistry& ParticleWorld::getParticleForceRegistry()
	{
		return m_forceRegistry;
	}

	const ParticleForceRegistry& ParticleWorld::getParticleForceRegistry() const
	{
		return m_forceRegistry;
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
}