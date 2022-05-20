#include "pch.h"
#include "TyphoonScene.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "ParticleTyphoon.h"
#include "ParticleCable.h"
#include "ParticleCollision.h"

TyphoonScene::TyphoonScene()
	: CaveScene(-9.807f, 10.0f, 50.0f, 30.0f),
	m_particleWorld(new PlacementParticleWorld)
{
#pragma region Exercise 7.1
	// Create Wind affected Particle
	auto tokyoitePlacement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(tokyoitePlacement);

	tokyoitePlacement->TranslateDelta(Vektoria::CHVector(
		m_caveDimensions.width * 0.5f,
		1.2f,
		-m_caveDimensions.depth * 0.5f));

	auto tokyoiteMaterial = new Vektoria::CMaterial();
	tokyoiteMaterial->LoadPreset((char*)"PhongRed");
	regMaterial(tokyoiteMaterial);
	auto tokyoiteGeo = new Vektoria::CGeoSphere();
	tokyoiteGeo->Init(1.2f, tokyoiteMaterial);

	auto tokyoite = new PlacementParticle(
		tokyoitePlacement,
		tokyoiteGeo,
		tokyoiteMaterial,
		0.999f,
		1.0f);

	auto typhoonForce = new Todes::ParticleTyphoon(
		1.2f,
		{},
		1.0f,
		2.5f,
		QUATERPI,
		0.05f,
		0.9f);

	m_particleWorld->addPlacementParticle(tokyoite, { typhoonForce });

	// Create Water Tanks
	auto tankMaterial = new Vektoria::CMaterial();
	tankMaterial->LoadPreset((char*)"Water");
	tankMaterial->SetTransparency(0.2f);
	regMaterial(tankMaterial);

	const auto tankHeight = m_caveDimensions.height * 0.05f;
	const auto tankThickness = 1.5f;

	// Left Water Barrier
	auto waterTank0 = new Vektoria::CPlacement();
	waterTank0->RotateY(UM_DEG2RAD(90.0f));
	waterTank0->TranslateXDelta(m_caveDimensions.thickness);
	m_pCave->AddPlacement(waterTank0);
	auto tankGeo0 = new Vektoria::CGeoWall();

	tankGeo0->Init(
		m_caveDimensions.depth,
		tankHeight,
		tankThickness,
		tankMaterial);

	waterTank0->AddGeo(tankGeo0);
	typhoonForce->addCalmSpace(
		{ convertVector(waterTank0->GetPos())
		, Todes::Vector3D(tankThickness, tankHeight, -m_caveDimensions.depth) });

	// Front Water Barrier
	auto waterTank1 = new Vektoria::CPlacement();
	waterTank1->TranslateZDelta(-m_caveDimensions.thickness - tankThickness);
	m_pCave->AddPlacement(waterTank1);
	auto tankGeo1 = new Vektoria::CGeoWall();

	tankGeo1->Init(
		m_caveDimensions.width,
		tankHeight,
		tankThickness,
		tankMaterial);

	waterTank1->AddGeo(tankGeo1);
	typhoonForce->addCalmSpace(
		{ convertVector(waterTank1->GetPos())
		, Todes::Vector3D(m_caveDimensions.width, tankHeight, tankThickness) });

	// Right Water Barrier
	auto waterTank2 = new Vektoria::CPlacement();
	waterTank2->RotateYDelta(UM_DEG2RAD(90.0f));
	waterTank2->TranslateXDelta(m_caveDimensions.width - m_caveDimensions.thickness - tankThickness);
	m_pCave->AddPlacement(waterTank2);

	waterTank2->AddGeo(tankGeo0);
	typhoonForce->addCalmSpace(
		{ convertVector(waterTank2->GetPos())
		, Todes::Vector3D(tankThickness, tankHeight, -m_caveDimensions.depth) });

	// Back Water Barrier
	auto waterTank3 = new Vektoria::CPlacement();
	waterTank3->TranslateZ(-m_caveDimensions.depth + m_caveDimensions.thickness);
	m_pCave->AddPlacement(waterTank3);

	waterTank3->AddGeo(tankGeo1);
	typhoonForce->addCalmSpace(
		{ convertVector(waterTank3->GetPos())
		, Todes::Vector3D(m_caveDimensions.width, tankHeight, tankThickness) });
#pragma endregion

#pragma region Exercise 7.2
	const auto basketBallPosition = Todes::Vector3D
		( m_caveDimensions.width * 0.5f
		, m_caveDimensions.height
		, -m_caveDimensions.depth * 0.5f);

	// Create anchor particle
	auto anchor = new Todes::Particle
	( basketBallPosition
	, 0.999f
	, 0.0f);

	// Create Basket Ball
	auto basketBallPlacement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(basketBallPlacement);

	basketBallPlacement->TranslateDelta(convertVector(basketBallPosition));

	auto basketBallMaterial = new Vektoria::CMaterial();
	basketBallMaterial->LoadPreset((char*)"PhongYellow");
	regMaterial(basketBallMaterial);
	auto basketBallGeo = new Vektoria::CGeoSphere();
	basketBallGeo->Init(1.0f, basketBallMaterial);

	auto basketBall = new PlacementParticle(
		basketBallPlacement,
		basketBallGeo,
		basketBallMaterial,
		0.999f,
		1.0f);
	
	// Create Basket Ball Contact Generator
	auto basketBallContact = new Todes::ParticleCable
		(m_caveDimensions.height - m_caveDimensions.thickness - 1.0f, 0.5f);
	basketBallContact->setParticles(basketBall->getParticle(), anchor);

	m_particleWorld->addPlacementParticle(basketBall, { m_gravity });
	m_particleWorld->addContacts({ basketBallContact });
#pragma endregion

#pragma region Exercise 7.3
	// Create Tennis Ball
	const auto tennisBallPosition = Todes::Vector3D
	(m_caveDimensions.width * 0.5f
		, m_caveDimensions.height + 3.0f
		, -m_caveDimensions.depth * 0.5f);

	auto tennisBallPlacement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(tennisBallPlacement);

	tennisBallPlacement->TranslateDelta(convertVector(tennisBallPosition));

	auto tennisBallMaterial = new Vektoria::CMaterial();
	tennisBallMaterial->LoadPreset((char*)"PhongGreen");
	regMaterial(tennisBallMaterial);
	auto tennisBallGeo = new Vektoria::CGeoSphere();
	tennisBallGeo->Init(0.5f, tennisBallMaterial);

	auto tennisBall = new PlacementParticle(
		tennisBallPlacement,
		tennisBallGeo,
		tennisBallMaterial,
		0.999f,
		2.0f);

	m_particleWorld->addPlacementParticle(tennisBall, { m_gravity });
	m_particleWorld->addContacts
	({
		new Todes::ParticleCollision(basketBall->getParticle(), tennisBall->getParticle(), 1.5f, 0.7f)
	});
#pragma endregion
// 	tennisBallPlacement->AddPlacement(&m_cameraPlacement);
// 	m_cameraPlacement.SetPointing(tennisBallPlacement);
}

TyphoonScene::~TyphoonScene()
{ }

void TyphoonScene::update(float timeDelta)
{
	m_particleWorld->update(timeDelta);
}

void TyphoonScene::reset()
{
	m_particleWorld->reset();
}
