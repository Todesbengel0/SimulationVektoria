#include "ParticleEngineCI.h"

namespace Todes
{
	ParticleEngineCI::~ParticleEngineCI()
		= default;

	void ParticleEngineCI::setParticleWorld(ParticleWorld* particleWorld)
	{
		m_particleWorld = particleWorld;
	}

	ParticleWorld* ParticleEngineCI::getParticleWorld() const
	{
		return m_particleWorld;
	}

	ParticleEngineCI::ParticleEngineCI(ParticleWorld* particleWorld /*= nullptr*/)
		: m_particleWorld(particleWorld)
	{
	}
}