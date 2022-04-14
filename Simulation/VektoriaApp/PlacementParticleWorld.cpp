#include "pch.h"
#include "PlacementParticleWorld.h"

#include "ParticleWorld.h"
#include "Particle.h"
#include "DefaultParticleEngineCI.h"
#include "PlacementParticle.h"

#pragma region Constructor & Destructor
PlacementParticleWorld::PlacementParticleWorld()
{
	m_world = std::make_unique<Todes::ParticleWorld>();

	const auto computationInterface = new Todes::DefaultParticleEngineCI(m_world.get());
	m_world->setComputationInterface(computationInterface);
}

PlacementParticleWorld::~PlacementParticleWorld()
	= default;
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

void PlacementParticleWorld::clear()
{
	for (auto& placementParticle : m_placementParticles)
		m_world->removeParticle(placementParticle->getParticle());
	m_placementParticles.clear();
}
#pragma endregion

void PlacementParticleWorld::update()
{
	for (auto& placementParticle : m_placementParticles)
		placementParticle->update();
}
