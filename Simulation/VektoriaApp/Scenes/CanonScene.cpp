#include "pch.h"
#include "Vektoria/Placement.h"
#include "Vektoria/GeoSphere.h"
#include "Vektoria/GeoCylinder.h"
#include "Scenes/CanonScene.h"

CanonScene::CanonScene()
{
	m_downForce = glm::vec3(0.0f, -9.807f, 0.0f);

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
}

CanonScene::~CanonScene()
{
	for (auto& pp : m_ppBalls)
	{
		if (pp->particle)
			delete pp->particle;
		if (pp->placement)
			delete pp->placement;
		delete pp;
	}
}

void CanonScene::update(float timeDelta)
{
	__super::update(timeDelta);
	for (auto pp : m_ppBalls)
	{
		if (!pp->particle || !pp->placement)
			continue;
		if (pp->particle->isDead())
			continue;
		auto force = pp->particle->getMass() * m_downForce;
		pp->particle->addForce(force);
		pp->particle->integrate(timeDelta);
		auto position = pp->particle->getPosition();
		auto vekvec = Vektoria::CHVector(position.x, position.y, position.z);
		pp->placement->Translate(vekvec);
	}
}

void CanonScene::reset()
{
	for (auto pp : m_ppBalls)
	{
		if (!pp->particle || !pp->placement)
			continue;
		if (pp->particle->isDead())
			continue;
		pp->particle->sendDeath();
		pp->placement->SwitchOff();
	}
}

void CanonScene::spawn()
{
	// new Ball
	m_ppBalls.push_back(new PlacementParticle);
	auto pp = m_ppBalls.back();

	// Initilize Placement
	pp->placement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(pp->placement);

	// Translate to Canon Base
	auto cp = m_canon.placement->GetPos();
	pp->placement->TranslateDelta(cp);

	// Initilize Geo and Material
	auto gBall = new Vektoria::CGeoSphere();
	pp->material = new Vektoria::CMaterial();
	pp->material->LoadPreset((char*)"MarbleWhite");
	regMaterial(pp->material);
	gBall->Init(1.0f, pp->material);
	pp->placement->AddGeo(gBall);
	pp->geo = gBall;

	
	// Get Canon Direction
	Vektoria::CHMat rotX;
	rotX.Init();
	rotX.RotateX(m_canon.xRotation);
	Vektoria::CHMat rotZ;
	rotZ.Init();
	rotZ.RotateZ(m_canon.zRotation);
	auto canonDirection = rotX * rotZ * Vektoria::CHVector(0.0f, m_canon.height * 0.5f, 0.0f);

	// Translate Ball to Muzzle
	pp->placement->TranslateDelta(canonDirection);
	
	// Get Particle Position (vec3) and Initilize Particle
	glm::vec3 particlePosition(pp->placement->GetPos().x, pp->placement->GetPos().y, pp->placement->GetPos().z);
	pp->particle = new ParticleDan(particlePosition, 0.999f, 1.0f);

	// Create Muzzle Force
	float muzzleVelocity = 20.0f;
	glm::vec3 shootDirection = glm::vec3(canonDirection.GetX(), canonDirection.GetY(), canonDirection.GetZ());
	glm::vec3 muzzleForce = shootDirection * (muzzleVelocity / shootDirection.length());
	
	// Add Muzzle Force
	pp->particle->addForce(muzzleForce);
	// Integrate once
	pp->particle->integrate(1.0f);
	auto position = pp->particle->getPosition();
	auto vekvec = Vektoria::CHVector(position.x, position.y, position.z);
	pp->placement->Translate(vekvec);
}
