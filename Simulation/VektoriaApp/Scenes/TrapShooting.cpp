#include "pch.h"
#include "TrapShooting.h"
#include "TodesConverter.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "Particle.h"
#include "Game.h"
#include "Random.h"
#include "ClayPiece.h"
#include "ClayPigeon.h"

TrapShooting::TrapShooting()
	: CaveScene(-9.897f, 40.0f, 50.0f, 20.0f, 25.0f, 0.1f)
	, m_particleWorld(new PlacementParticleWorld)
	, m_ballRadius(0.2f)
{
	setWASDCam(false);
	Todes::Random::seed();

#pragma region Canon
	m_canon.transPlacement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(m_canon.transPlacement);
	m_canon.transPlacement->TranslateXDelta(20.0f);
	m_canon.transPlacement->TranslateYDelta(10.0f - m_canon.height * 0.5f);
	m_canon.transPlacement->TranslateZDelta(7.0f);

	m_canon.rotPlacement = new Vektoria::CPlacement();
	m_canon.transPlacement->AddPlacement(m_canon.rotPlacement);
	m_canon.rotPlacement->TranslateY(m_canon.height * 0.5f);
	m_canon.rotPlacement->RotateXDelta(UM_DEG2RAD(-45.0f));

	m_canon.geo = new Vektoria::CGeoCylinder();
	m_canon.material = new Vektoria::CMaterial();
	m_canon.material->LoadPreset((char*)"MetalRustyFlaking");
	regMaterial(m_canon.material);
	m_canon.geo->Init(2.5f, 1.5f, m_canon.height, m_canon.material);
	m_canon.rotPlacement->AddGeo(m_canon.geo);

	// Initialize Geo and Material
	m_geoBall = new Vektoria::CGeoSphere();
	m_materialBall = new Vektoria::CMaterial();
	m_materialBall->LoadPreset((char*)"MarbleWhite");
	regMaterial(m_materialBall);
	m_geoBall->Init(m_ballRadius, m_materialBall);
#pragma endregion
}

void TrapShooting::update(float timeDelta)
{
	m_particleWorld->update(timeDelta);
	moveCanon(timeDelta);
	checkBalls();
}

void TrapShooting::spawn()
{
	// new Ball
	auto placementBall = new Vektoria::CPlacement();
	m_pCave->AddPlacement(placementBall);

	// Translate to Canon Base
	auto cp = m_canon.transPlacement->GetPos();
	placementBall->TranslateDelta(cp);

	// Get Canon Direction
	auto canonDirection = m_canon.rotPlacement->GetPos();
	canonDirection *= 2.0f;

	// Translate Ball to Muzzle
	placementBall->TranslateDelta(canonDirection);

	// Get Particle Position (Vector3D) and Initialize Particle
	auto ball = new PlacementParticle(placementBall, m_geoBall, m_materialBall, 0.999f, 1.0f);
	m_balls.push_back(ball);
	m_particleWorld->addPlacementParticle(ball, { m_gravity });

	// Create Muzzle Force
	float muzzleVelocity = 20.0f;
	Todes::Vector3D shootDirection(convertVector(canonDirection));
	Todes::Vector3D muzzleForce = shootDirection * (muzzleVelocity / shootDirection.Length());
	ball->getParticle()->setVelocity(muzzleForce);
}

void TrapShooting::moveCanon(const float& timeDelta)
{
	auto& keyboard = CGame::GetInstance().getKeyboard();

	if (keyboard.KeyDown(DIK_ADD))
		m_canon.movementSpeed += 0.5f;
	if (keyboard.KeyDown(DIK_SUBTRACT))
		m_canon.movementSpeed -= 0.5f;
	if (keyboard.KeyDown(DIK_PERIOD))
		m_canon.rotationSpeed += 0.1f;
	if (keyboard.KeyDown(DIK_COMMA))
		m_canon.rotationSpeed -= 0.1f;
	m_canon.movementSpeed = std::fmaxf(0.0f, m_canon.movementSpeed);
	m_canon.rotationSpeed = std::clamp(m_canon.rotationSpeed, 0.0f, TWOPI);

	const auto movementSpeed = m_canon.movementSpeed * timeDelta;
	const auto rotationSpeed = m_canon.rotationSpeed * timeDelta;
	
	Vektoria::CHVector positionalDifference;
	
	if (keyboard.KeyPressed(DIK_A))
		positionalDifference.x -= 1.0f;

	if (keyboard.KeyPressed(DIK_D))
		positionalDifference.x += 1.0f;

	Vektoria::CHVector rotationAxis;

	if (keyboard.KeyPressed(DIK_W))
		rotationAxis.x += 1.0f;

	if (keyboard.KeyPressed(DIK_S))
		rotationAxis.x -= 1.0f;

	if (keyboard.KeyPressed(DIK_Q))
		rotationAxis.z += 1.0f;

	if (keyboard.KeyPressed(DIK_E))
		rotationAxis.z -= 1.0f;

	if (!positionalDifference.IsNull())
		m_canon.transPlacement->TranslateDelta(positionalDifference.GetNormal() * movementSpeed);

	if (!rotationAxis.IsNull())
		m_canon.rotPlacement->RotateDelta(rotationAxis.GetNormal(), rotationSpeed);
}

void TrapShooting::checkBalls()
{
	while (m_balls.begin() != m_balls.end())
	{
		auto firstBall = m_balls.begin();

		if (((*firstBall)->getPlacement()->GetPos().z + m_ballRadius >= -m_caveDimensions.depth)
			&& ((*firstBall)->getPlacement()->GetPos().y + m_ballRadius >= 0.0f))
			return;

		(*firstBall)->getPlacement()->SwitchOff();
		(*firstBall)->destroy();
		m_balls.erase(firstBall);
	}
}

void TrapShooting::registerClayPiece(ClayPiece* piece)
{
	m_pCave->AddPlacement(piece->getPlacement());
	m_particleWorld->addPlacementParticle(piece, { m_gravity });
}
