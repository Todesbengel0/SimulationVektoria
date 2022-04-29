#include "ParticleForceRegistry.h"
#include "Particle.h"
#include "IParticleForceGenerator.h"

#include <algorithm>

namespace Todes
{
	ParticleForceRegistry::ParticleForceRegistry()
	{
	}

	ParticleForceRegistry::~ParticleForceRegistry()
	{
	}

	void ParticleForceRegistry::add(Particle* particle, IParticleForceGenerator* generator)
	{
		m_registrations.push_back(ParticleForceRegistrationEntry{ particle, generator });
	}

	void ParticleForceRegistry::add(Particle* particle, std::initializer_list<IParticleForceGenerator*> generators)
	{
		std::for_each(generators.begin(), generators.end(),
			[&](IParticleForceGenerator* generator)
			{
				m_registrations.push_back(ParticleForceRegistrationEntry{ particle, generator });
			});
	}

	bool ParticleForceRegistry::remove(Particle* particle, IParticleForceGenerator* generator)
	{
		const auto removableItem = std::remove_if(m_registrations.begin(), m_registrations.end(),
			[&](const ParticleForceRegistrationEntry& entry)
			{
				return entry.m_particle == particle && entry.m_forceGenerator == generator;
			});

		if (removableItem == m_registrations.end())
			return false;

		m_registrations.erase(removableItem);
		return true;
	}

	bool ParticleForceRegistry::remove(Particle* particle)
	{
		const auto removableItem = std::remove_if(m_registrations.begin(), m_registrations.end(),
			[&](const ParticleForceRegistrationEntry& entry)
			{
				return entry.m_particle == particle;
			});

		if (removableItem == m_registrations.end())
			return false;

		m_registrations.erase(removableItem, m_registrations.end());
		return true;
	}

	void ParticleForceRegistry::clear()
	{
		m_registrations.clear();
	}

	void ParticleForceRegistry::updateForces()
	{
		for (auto& entry : m_registrations)
			entry.m_forceGenerator->updateForce(entry.m_particle);
	}
}