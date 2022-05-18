#include "pch.h"
#include "Scenes/FireworkScene.h"
#include "TodesConverter.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "Particle.h"
#include "Random.h"
#include "Firework.h"
#include "CGeoTail.h"

PlacementParticleWorld* FireworkScene::getWorld() const
{
	return m_particleWorld;
}

void FireworkScene::registerFirework(Firework* firework) const
{
	m_pCave->AddPlacement(firework->getPlacement());
	m_particleWorld->addPlacementParticle(firework, { m_gravity });
}

void FireworkScene::removeFirework(Firework* firework) const
{
	m_pCave->SubPlacement(firework->getPlacement());
}

FireworkScene::FireworkScene()
	: CaveScene(-9.807f, 25.0f, 40.0f, 20.0f, 30.0f),
	m_particleWorld(new PlacementParticleWorld),
	m_fireworkMaterial(new Vektoria::CMaterial()),
	m_tailGeo(new Vektoria::CGeoTail(*m_fireworkMaterial))
{
	m_cameraPlacement.TranslateZDelta(20.0f);
	const auto pos = m_backWall.placement->GetPos();

	m_backWall.placement->TranslateDelta(pos.x - 100.0f, pos.y - 25.0f, pos.z - 50.0f);
	auto stars = new Vektoria::CMaterial();
	stars->LoadPreset((char*)"SkyStarfieldLowRes");
	regMaterial(stars);
	m_backWall.geo->Init(409.6f, 102.4f, m_caveDimensions.thickness, stars, false, false, false, false, true, false);

	m_leftWall.placement->SwitchOff();
	m_rightWall.placement->SwitchOff();
	m_ceiling.placement->SwitchOff();
/*	m_frontWall.placement->SwitchOff();*/

	m_tail = new Vektoria::CTailPlacements(m_pCave, m_tailGeo, 10000, 0.7f);

	Todes::Random::seed();
	m_fireworkMaterial->LoadPreset((char*)"Sun");
	regMaterial(m_fireworkMaterial);
	m_fireworkMaterial->SetGlowStrength(3.1f);

	auto geo = new Vektoria::CGeoSphere();
	geo->Init(1.0f, m_fireworkMaterial);
	m_fireworkGeo = geo;
}

FireworkScene::~FireworkScene()
{
	delete m_particleWorld;
}

void FireworkScene::update(float timeDelta)
{
	m_particleWorld->update(timeDelta);
	m_tail->update(timeDelta);
}

void FireworkScene::spawn()
{
	// Initialize Placement
	auto fireworkPlacement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(fireworkPlacement);

	// Translate Placement to random position in range
	fireworkPlacement->TranslateDelta(convertVector(Todes::Random::Vec3D
	(Todes::Vector3D(0.0f, 0.0f, -m_caveDimensions.depth)
	, Todes::Vector3D(m_caveDimensions.width, 0.0f, 0.0f))));

	// Create Muzzle Force
	float muzzleVelocity = Todes::Random::Float(30.0f, 45.0f);
	Todes::Vector3D shootDirection(0.0f, 1.0f, 0.0f);
	Todes::Vector3D muzzleForce = shootDirection * muzzleVelocity;

	const Firework::PayloadBounds bounds
	{
		0.5f /* ageMin */
		, Todes::Random::Float(0.5f, 0.8f) /* ageMax */
		, 15 /* countMin */
		, Todes::Random::Size_t(15, 35) /* countMax */
		, 0.1f /* massMin */
		, Todes::Random::Float(0.1f, 5.0f) /* massMax */
		, 0.05f /* sizeMin */
		, Todes::Random::Float(0.2f, 0.3f) /* sizeMax */
		, 5.0f /* velocityMin */
		, (muzzleVelocity - 5.0f) * 0.2f + 5.0f /* velocityMax */
	};

	m_fireworkMaterial->RotateHue(UM_DEG2RAD(Todes::Random::Float(0.0f, 360.0f)));
	auto firework = new Firework(fireworkPlacement, this, m_tail, m_fireworkGeo, m_fireworkMaterial, 2, bounds);
	m_particleWorld->addPlacementParticle(firework, { m_gravity });

	// Add Muzzle Force
	firework->getParticle()->setVelocity(muzzleForce);
}
