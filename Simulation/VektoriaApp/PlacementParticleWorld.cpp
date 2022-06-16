#include "pch.h"
#include "PlacementParticleWorld.h"

#include "ParticleWorld.h"
#include "Particle.h"
#include "DefaultParticleEngineCI.h"
#include "PlacementParticle.h"
#include "ForceDefines.h"

#pragma region Constructor & Destructor
PlacementParticleWorld::PlacementParticleWorld()
{
	m_world = std::make_unique<Todes::ParticleWorld>(100);
}

PlacementParticleWorld::~PlacementParticleWorld()
{
	for (std::size_t i = 0; i < m_placementParticles.size(); ++i)
		deletePlacementParticle(m_placementParticles.begin() + i--);
}
#pragma endregion

#pragma region Getter & Setter
const PlacementParticleWorld::Particles& PlacementParticleWorld::getParticles() const
{
	return m_world->getParticles();
}

PlacementParticleWorld::Particles& PlacementParticleWorld::getParticles()
{
	return m_world->getParticles();
}

PlacementParticleWorld::PlacementParticles& PlacementParticleWorld::getPlacementParticles()
{
	return m_placementParticles;
}

Todes::ParticleWorld* PlacementParticleWorld::getWorld() const
{
	return m_world.get();
}
#pragma endregion

#pragma region Add & Remove Functions
void PlacementParticleWorld::addPlacementParticle(PlacementParticle* placement)
{
	m_placementParticles.push_back(placement);
	m_world->addParticle(placement->getParticle());
}

void PlacementParticleWorld::addPlacementParticle(PlacementParticle* placement, ForceGeneratorList generators)
{
	addPlacementParticle(placement);
	m_world->getParticleForceRegistry().add(placement->getParticle(), generators);
}

bool PlacementParticleWorld::addForces(PlacementParticle* placement, ForceGeneratorList generators)
{
	bool isRegistered = std::count(m_placementParticles.begin(), m_placementParticles.end(), placement) > 0;
	
	if (!isRegistered)
		return false;

	m_world->getParticleForceRegistry().add(placement->getParticle(), generators);

	return true;
}

void PlacementParticleWorld::addForces(ForceGeneratorList generators)
{
	for (auto pp : m_placementParticles)
		m_world->getParticleForceRegistry().add(pp->getParticle(), generators);
}

void PlacementParticleWorld::addContacts(ContactGeneratorList contacts)
{
	m_world->getParticleContactRegistry().add(contacts);
}

bool PlacementParticleWorld::removePlacementParticle(PlacementParticle* placement)
{
	const auto removablePlacement = std::remove(m_placementParticles.begin(),
												m_placementParticles.end(),
												placement);

	if (removablePlacement == m_placementParticles.end())
		return false;

	m_world->removeParticle(placement->getParticle());
	m_placementParticles.erase(removablePlacement);

	return true;
}

bool PlacementParticleWorld::deletePlacementParticle(PlacementParticles::iterator placementParticleIt)
{
	auto placementParticle = *placementParticleIt;

	auto particle = placementParticle->getParticle();
	auto placement = placementParticle->getPlacement();
	m_world->removeParticle(particle);
	m_world->getParticleForceRegistry().remove(particle);

	// VEKTORIA
	m_placementParticles.erase(placementParticleIt);
	
	delete particle;
	delete placement;
	delete placementParticle;

	return true;
}

void PlacementParticleWorld::clear()
{
	for (auto& placementParticle : m_placementParticles)
		m_world->removeParticle(placementParticle->getParticle());
	m_placementParticles.clear();
}
#pragma endregion

void PlacementParticleWorld::update(float timeDelta)
{
	m_world->updateWorld(timeDelta);

	// Translates the Placements
	for (std::size_t i = 0; i < m_placementParticles.size(); ++i)
	{
		auto currentPP = m_placementParticles[i];
		currentPP->update(timeDelta);

		if (currentPP->isDirty())
		{
			deletePlacementParticle(m_placementParticles.begin() + i);
			--i;
		}
	}

}

void PlacementParticleWorld::reset() const
{
	m_world->reset();

	for (auto placementParticle : m_placementParticles)
		placementParticle->reset();
}

void PlacementParticleWorld::kill() const
{
	for (auto placementParticle : m_placementParticles)
		placementParticle->kill();
}

void PlacementParticleWorld::revive() const
{
	for (auto placementParticle : m_placementParticles)
		placementParticle->revive();
}
