#include "pch.h"
#include "SolarSystem.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "ParticleCable.h"
#include "Random.h"

SolarSystem::SolarSystem()
	: m_particleWorld(new PlacementParticleWorld)
	, m_sunPlacement(new Vektoria::CPlacement)
{
	Todes::Random::seed();

	m_cameraPlacement.TranslateZDelta(250.0f);

	m_planetMaterial.LoadPreset((char*)"EarthCracked");
	regMaterial(&m_planetMaterial);
	m_planetGeo.Init(1.0f, &m_planetMaterial);

	// Create the Sun
	AddPlacement(m_sunPlacement);
	auto sunMaterial = new Vektoria::CMaterial();
	sunMaterial->LoadPreset((char*)"Sun");
	regMaterial(sunMaterial);
	auto sunGeo = new Vektoria::CGeoSphere();
	sunGeo->Init(5.0f, sunMaterial);
	m_sun = new PlacementParticle(m_sunPlacement, sunGeo, sunMaterial, 1.0f, 0.0f);

	// Create Planets
	Todes::Vector3D baseVelocity(-1.0f, 0.0f, 0.0f);

	for (int i = 0; i < 6; ++i)
	{
		const float radius = (i + 1) * 0.75f;
		const float inverseMass = 1.0f / float(i + 1);
		const float speed = Todes::Random::Float(4.0f, 10.0f);
		const float distance = 10.0f * (i + 1);

		auto planetPlacement = new Vektoria::CPlacement();
		planetPlacement->TranslateY(distance);
		AddPlacement(planetPlacement);
		auto planetGeoPlacement = new Vektoria::CPlacement();
		planetGeoPlacement->AddGeo(&m_planetGeo);
		planetGeoPlacement->ScaleDelta(radius);
		planetPlacement->AddPlacement(planetGeoPlacement);
		m_planets.push_back(planetGeoPlacement);

		auto planet = new PlacementParticle(planetPlacement, 0.999f, inverseMass);
		m_particleWorld->addPlacementParticle(planet);

		planet->getParticle()->setVelocity(baseVelocity * speed);

		auto connection = new Todes::ParticleCable(distance, 0.0f);
		connection->setParticles(planet->getParticle(), m_sun->getParticle());

		m_particleWorld->addContacts({ connection });
	}
}

SolarSystem::~SolarSystem()
{
	delete m_particleWorld;
	delete m_sun;
}

void SolarSystem::update(float timeDelta)
{
	m_particleWorld->update(timeDelta);

	m_sunPlacement->RotateYDelta(timeDelta * HALFPI * 0.1f);

	for (auto planet : m_planets)
	{
		planet->RotateXDelta(timeDelta * HALFPI * 0.05f);
		planet->RotateYDelta(timeDelta * HALFPI * 0.05f);
	}
}

void SolarSystem::reset()
{
	m_particleWorld->reset();
}
