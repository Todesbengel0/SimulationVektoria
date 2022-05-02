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

void FireworkScene::registerFirework(Firework* firework, Vektoria::CTailPlacements* tail)
{
	m_pCave->AddPlacement(firework->getPlacement());
	m_particleWorld->addPlacementParticle(firework, { m_gravity });
	regMaterial(firework->getMaterial());
	m_tails.push_back(tail);
	tail->Init(m_pCave);
}

FireworkScene::FireworkScene()
	: CaveScene(25.0f),
	m_particleWorld(new PlacementParticleWorld),
	m_gravity(new Gravity(convertVector(Vektoria::CHVector(0.0f, -9.807f, 0.0f)))),
	m_fireworkMaterial(new Vektoria::CMaterial())
{
	Todes::Random::seed();
	m_fireworkMaterial->LoadPreset((char*)"Sun");
	regMaterial(m_fireworkMaterial);
	m_fireworkMaterial->SetGlowStrength(3.1f);
}

FireworkScene::~FireworkScene()
= default;

void FireworkScene::update(float timeDelta)
{
	m_particleWorld->update(timeDelta);

	for (std::size_t i = 0; i < m_tails.size(); ++i)
	{
		auto tail = m_tails[i];

		if (!tail->isDirty())
		{
			tail->update(timeDelta);
			continue;
		}

		//delete tail;
		m_tails.erase(m_tails.begin() + i);
		--i;
	}
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
	float muzzleVelocity = Todes::Random::Float(25.0f, 40.0f);
	Todes::Vector3D shootDirection(0.0f, 1.0f, 0.0f);
	Todes::Vector3D muzzleForce = shootDirection * muzzleVelocity;

	const Firework::PayloadBounds bounds
	{
		0.5f /* ageMin */
		, Todes::Random::Float(0.5f, 0.7f) /* ageMax */
		, 5 /* countMin */
		, Todes::Random::Size_t(5, 10) /* countMax */
		, 0.1f /* massMin */
		, Todes::Random::Float(0.1f, 5.0f) /* massMax */
		, 0.1f /* sizeMin */
		, Todes::Random::Float(0.1f, 0.3f) /* sizeMax */
		, 5.0f /* velocityMin */
		, (muzzleVelocity - 5.0f) * 0.4f + 5.0f /* velocityMax */
	};

	m_fireworkMaterial->RotateHue(UM_DEG2RAD(Todes::Random::Float(0.0f, 360.0f)));
	auto firework = new Firework(fireworkPlacement, this, m_fireworkMaterial, 2, bounds);
	m_particleWorld->addPlacementParticle(firework, { m_gravity });

	// Add Muzzle Force
	firework->getParticle()->addForce(muzzleForce);
	firework->getParticle()->integrate(1.0f);
	firework->update();
}
