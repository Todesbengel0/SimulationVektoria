#include "DefaultParticleEngineCI.h"
#include "ParticleWorld.h"
#include "Particle.h"

#include <cassert>
#include <memory>

namespace Todes
{
	DefaultParticleEngineCI::DefaultParticleEngineCI(ParticleWorld* particleWorld /*= nullptr*/)
		: ParticleEngineCI(particleWorld)
	{
		reset();
	}

	DefaultParticleEngineCI::~DefaultParticleEngineCI()
		= default;

	void DefaultParticleEngineCI::onBegin()
	{
		assert(m_particleWorld != nullptr);
	}

	void DefaultParticleEngineCI::step(float timeDelta)
	{
		assert(m_particleWorld != nullptr);

		auto& registry = m_particleWorld->getParticleForceRegistry();
		registry.updateForces();
	}

	void DefaultParticleEngineCI::integrate(float timeDelta)
	{
		assert(m_particleWorld != nullptr);

		auto& particles = m_particleWorld->getParticles();
		for (auto particle : particles)
			particle->integrate(timeDelta);
	}

	void DefaultParticleEngineCI::onEnd()
	{
		assert(m_particleWorld != nullptr);
	}

	void DefaultParticleEngineCI::reset()
	{

	}
}