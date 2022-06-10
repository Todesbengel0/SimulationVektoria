#include "pch.h"
#include "SpaceshipScene.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "ParticlePlanetGravityForce.h"
#include "Random.h"

SpaceshipScene::SpaceshipScene()
	: m_particleWorld(new PlacementParticleWorld)
	, m_gravityConstant(1.0f)
{
	Todes::Random::seed();

	m_planetMaterial.LoadPreset((char*)"EarthCracked");
	regMaterial(&m_planetMaterial);
	m_planetGeo.Init(1.0f, &m_planetMaterial);

	// Create Spaceship
	Vektoria::CPlacement* spaceshipPlacement = new Vektoria::CPlacement();
	AddPlacement(spaceshipPlacement);
	Vektoria::CPlacement* geoPlacement = new Vektoria::CPlacement();
	geoPlacement->RotateYDelta(HALFPI);
	spaceshipPlacement->AddPlacement(geoPlacement);
	
	Vektoria::CMaterial* spaceshipMaterial = new Vektoria::CMaterial();
	spaceshipMaterial->LoadPreset((char*)"RockVerySnowy");
	regMaterial(spaceshipMaterial);

	Vektoria::CGeoUtahTeapot* spaceshipGeo = new Vektoria::CGeoUtahTeapot();
	spaceshipGeo->Init(2.0f, spaceshipMaterial);
	geoPlacement->AddGeo(spaceshipGeo);

	PlacementParticle* spaceship = new PlacementParticle(spaceshipPlacement, 0.999f, 0.001f);
	spaceship->getParticle()->setVelocity(Todes::Vector3D(0.0f, 0.0f, -250.0f));

	m_particleWorld->addPlacementParticle(spaceship);

	// Create Planets
	for (std::size_t i = 0; i < 2000; ++i)
	{
		const float radius = (i + 1.0f) * 0.25f;
//		const float t = i * HALFPI * 0.3f;
		const float t = Todes::Random::FloatNorm() * TWOPI;
		const float r = 15.0f + i;
		Vektoria::CHVector position = Vektoria::CHVector(r * std::cosf(t), r * std::sinf(t), - radius * 1000.0f, 1.0f);
		auto planet = createPlanet(position, radius);
//		m_particleWorld->addPlacementParticle(planet);

		auto gravity = new Todes::ParticlePlanetGravityForce(planet->getParticle(), m_gravityConstant);
		gravity->setInnerRange(radius * 2.0f);
		gravity->setOuterRange(radius * 500.0f);

		m_particleWorld->addForces(spaceship, { gravity });
	}

	spaceshipPlacement->AddPlacement(&m_cameraPlacement);
	m_cameraPlacement.TranslateYDelta(5.0f);
	m_cameraPlacement.TranslateZDelta(60.0f);
}

SpaceshipScene::~SpaceshipScene()
{
	delete m_particleWorld;
}

void SpaceshipScene::update(float timeDelta)
{
	m_particleWorld->update(timeDelta);
}

void SpaceshipScene::reset()
{
	m_particleWorld->reset();
}

PlacementParticle* SpaceshipScene::createPlanet(const Vektoria::CHVector& position, const float& radius)
{
	// Create Planet Placement
	Vektoria::CPlacement* planetPlacement = new Vektoria::CPlacement();
	AddPlacement(planetPlacement);
	planetPlacement->Scale(radius);
	planetPlacement->TranslateDelta(position);

	// Create Placement Particle
	PlacementParticle* particle = new PlacementParticle(planetPlacement, &m_planetGeo, &m_planetMaterial, 0.999f, 0.0f);
	return particle;
}