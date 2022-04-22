#include "pch.h"
#include "Vektoria/Placement.h"
#include "Vektoria/GeoSphere.h"
#include "Vektoria/GeoCylinder.h"
#include "Scenes/CanonScene.h"
#include "TodesConverter.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "Particle.h"

CanonScene::CanonScene()
	: m_particleWorld(new PlacementParticleWorld),
	m_gravity(new Gravity(convertVector(Vektoria::CHVector(0.0f, -9.807f, 0.0f))))
{
//	m_downForce = Todes::Vector3D(0.0f, -9.807f, 0.0f);

	m_canon.placement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(m_canon.placement);
	m_canon.placement->RotateZDelta(m_canon.zRotation = UM_DEG2RAD(25.0f));
	m_canon.placement->RotateXDelta(m_canon.xRotation = UM_DEG2RAD(-10.0f));
	m_canon.placement->TranslateXDelta(20.0f);
	m_canon.placement->TranslateYDelta(0.5f);
	m_canon.placement->TranslateZDelta(-10.0f);
	
	auto canonGeo = new Vektoria::CGeoCylinder();
	m_canon.material = new Vektoria::CMaterial();
	m_canon.material->LoadPreset((char*)"MetalRustyFlaking");
	regMaterial(m_canon.material);
	canonGeo->Init(2.5f, 1.5f, m_canon.height = 5.0f, m_canon.material);
	m_canon.placement->AddGeo(canonGeo);
	m_canon.geo = canonGeo;

	// Initialize Geo and Material
	m_geoBall = new Vektoria::CGeoSphere();
	m_materialBall = new Vektoria::CMaterial();
	m_materialBall->LoadPreset((char*)"MarbleWhite");
	regMaterial(m_materialBall);
	m_geoBall->Init(1.0f, m_materialBall);
}

CanonScene::~CanonScene()
{
// 	for (auto& pp : m_ppBalls)
// 	{
// 		if (pp->getParticle())
// 			delete pp->getParticle();
// 		if (pp->getPlacement())
// 			delete pp->getPlacement();
// 		delete pp;
// 	}
}

void CanonScene::update(float timeDelta)
{
	__super::update(timeDelta);
// 	for (auto pp : m_ppBalls)
// 	{
// 		if (!pp->getParticle() || !pp->getPlacement())
// 			continue;
// 		if (pp->getParticle()->isDead())
// 			continue;
// 		auto force = pp->getParticle()->getMass() * m_downForce;
// 		pp->getParticle()->addForce(force);
// 		pp->getParticle()->integrate(timeDelta);
// 		auto position = pp->getParticle()->getPosition();
// 		auto vekvec = Vektoria::CHVector(position.x(), position.y(), position.z());
// 		pp->getPlacement()->Translate(vekvec);
// 	}

	m_particleWorld->update(timeDelta);
}

void CanonScene::reset()
{
// 	for (auto pp : m_ppBalls)
// 	{
// 		if (!pp->getParticle() || !pp->getPlacement())
// 			continue;
// 		if (pp->getParticle()->isDead())
// 			continue;
// 		pp->getParticle()->sendDeath();
// 		pp->getPlacement()->SwitchOff();
// 	}

	m_particleWorld->kill();
	m_particleWorld->clear();
}

void CanonScene::spawn()
{
	// new Ball
// 	m_ppBalls.push_back(new PlacementParticle);
// 	auto pp = m_ppBalls.back();
	

	// Initialize Placement
// 	pp->setPlacement(new Vektoria::CPlacement());
// 	m_pCave->AddPlacement(pp->getPlacement());
	auto placementBall = new Vektoria::CPlacement();
	m_pCave->AddPlacement(placementBall);

	// Translate to Canon Base
	auto cp = m_canon.placement->GetPos();
	//pp->getPlacement()->TranslateDelta(cp);
	placementBall->TranslateDelta(cp);
	
	// Get Canon Direction
	Vektoria::CHMat rotX;
	rotX.Init();
	rotX.RotateX(m_canon.xRotation);
	Vektoria::CHMat rotZ;
	rotZ.Init();
	rotZ.RotateZ(m_canon.zRotation);
	auto canonDirection = rotX * rotZ * Vektoria::CHVector(0.0f, m_canon.height * 0.5f, 0.0f);

	// Translate Ball to Muzzle
//	pp->getPlacement()->TranslateDelta(canonDirection);
	placementBall->TranslateDelta(canonDirection);
	
	// Get Particle Position (Vector3D) and Initialize Particle
//	pp->setParticle(new Todes::Particle(convertVector(pp->getPlacement()->GetPos()), 0.999f, 1.0f));
	auto ball = new PlacementParticle(placementBall, m_geoBall, m_materialBall, 0.999f, 1.0f);
	m_particleWorld->addPlacementParticle(ball, { m_gravity });


	// Create Muzzle Force
	float muzzleVelocity = 20.0f;
	Todes::Vector3D shootDirection(convertVector(canonDirection));
	Todes::Vector3D muzzleForce = shootDirection * (muzzleVelocity / shootDirection.Length());
	
	// Add Muzzle Force
// 	pp->getParticle()->addForce(muzzleForce);
	ball->getParticle()->addForce(muzzleForce);

 	// Integrate once
// 	pp->getParticle()->integrate(1.0f);
// 	auto vekvec = Vektoria::CHVector(convertVector(pp->getParticle()->getPosition()));
// 	pp->getPlacement()->Translate(vekvec);
	ball->getParticle()->integrate(1.0f);
	ball->update();
}
