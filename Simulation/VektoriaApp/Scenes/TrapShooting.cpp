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
#include "Mockingbird.h"

TrapShooting::TrapShooting()
	: CaveScene(-9.897f, 40.0f, 50.0f, 20.0f, 25.0f, 0.1f)
	, m_particleWorld(new PlacementParticleWorld)
	, m_ballRadius(0.2f)
	, m_score(5.0)
{
	setWASDCam(false);
	Todes::Random::seed();

#pragma region Canon
	m_canon.transPlacement = new Vektoria::CPlacement();
	m_canon.transPlacement->TranslateXDelta(20.0f);
	m_canon.transPlacement->TranslateYDelta(5.0f - m_canon.height * 0.5f);
	m_canon.transPlacement->TranslateZDelta(7.0f);
	m_pCave->AddPlacement(m_canon.transPlacement);

	m_canon.rotPlacement = new Vektoria::CPlacement();
	m_canon.rotPlacement->TranslateYDelta(m_canon.height * 0.5f);
	m_canon.rotPlacement->RotateXDelta(UM_DEG2RAD(-45.0f));
	m_canon.transPlacement->AddPlacement(m_canon.rotPlacement);

	m_canon.material = new Vektoria::CMaterial();
	m_canon.geo = new Vektoria::CGeoCylinder();
	m_canon.material->LoadPreset((char*)"MetalRustyFlaking");
	regMaterial(m_canon.material);
	m_canon.geo->Init(1.8f, 0.7f, m_canon.height, m_canon.material);
	m_canon.rotPlacement->AddGeo(m_canon.geo);

	// Initialize Geo and Material
	m_geoBall = new Vektoria::CGeoSphere();
	m_materialBall = new Vektoria::CMaterial();
	m_materialBall->LoadPreset((char*)"LeatherBlack");
	regMaterial(m_materialBall);
	m_geoBall->Init(m_ballRadius, m_materialBall);
#pragma endregion

#pragma region Pigeon
	m_clayPieceMaterial = new Vektoria::CMaterial();
	m_clayPieceMaterial->LoadPreset((char*)"PhongGrey");
	regMaterial(m_clayPieceMaterial);
	m_clayPieceGeo = new Vektoria::CGeoSphere();
	m_clayPieceGeo->Init(1.0f, m_clayPieceMaterial);

	for (unsigned int i = 0; i < m_pigeons.count; ++i)
	{
		m_pigeons.materials[i] = new Vektoria::CMaterial();
		m_pigeons.materials[i]->LoadPreset((char*)"PhongGrey");
		regMaterial(m_pigeons.materials[i]);
		m_pigeons.geos[i] = new Vektoria::CGeoSphere();
		m_pigeons.geos[i]->Init(1.0f, m_pigeons.materials[i]);

		m_pigeons.pigeons[i] = nullptr;
	}

	createPigeon();
#pragma endregion

#pragma region Mockingbird
	auto mockingPlacement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(mockingPlacement);
	auto mockingMaterial = new Vektoria::CMaterial();
	mockingMaterial->LoadPreset((char*)"PhongBlue");
	regMaterial(mockingMaterial);
	auto mockingGeo = new Vektoria::CGeoSphere();
	mockingGeo->Init(0.3f, mockingMaterial);

	m_mockingbird = new Mockingbird(mockingPlacement, mockingGeo, mockingMaterial, this
		, Mockingbird::Bounds
		{ m_caveDimensions.thickness + 0.6f, m_caveDimensions.width - m_caveDimensions.thickness - 0.6f
		, -m_caveDimensions.depth + m_caveDimensions.thickness + 0.6f, -m_caveDimensions.thickness - 0.6f
		, m_caveDimensions.height - m_caveDimensions.thickness, m_caveDimensions.height * 0.6f, m_caveDimensions.height * 0.8f
		, m_caveDimensions.height * 0.15f }, 0.3f);
	m_particleWorld->addPlacementParticle(m_mockingbird);
	auto looseparticle = new PlacementParticle(new Vektoria::CPlacement(), m_mockingbird->getLooseAnchor());
	m_particleWorld->addPlacementParticle(looseparticle);
	m_particleWorld->addForces(m_mockingbird, { m_mockingbird->getLooseForce() });
	const auto& forces = m_mockingbird->getAnchoredForces();
	for (auto force : forces)
		m_particleWorld->addForces(looseparticle, { force });

#pragma endregion

#pragma region Score
	m_scoreMaterial.LoadPreset("SpriteWhite");
	regMaterial(&m_scoreMaterial);
	m_scoreWritingFont.LoadPreset("OCRAExtendedBlack");
	m_scoreWritingFont.SetChromaKeyingOn();

	m_scoreOverlay.Init(&m_scoreMaterial, Vektoria::C2dRect(0.8f, 0.1f, 0.1, 0.05));
	m_scoreWriting.Init(Vektoria::C2dRect(0.76f, 0.06f, 0.12f, 0.07f), 70, &m_scoreWritingFont);

	m_scoreOverlay.SetLayer(0.2f);
	m_scoreWriting.SetLayer(0.1f);

	CGame::GetInstance().getViewport().AddOverlay(&m_scoreOverlay);
	CGame::GetInstance().getViewport().AddWriting(&m_scoreWriting);

	m_scoreWriting.PrintF("Current Score: %5.2f\tHighscore: %5.2f\tTime since Hit: %4.2f", 0.0, 0.0, 0.0f);
#pragma endregion

#pragma region Controls
	m_controlsMaterial.LoadPreset("SpriteBlack");
	regMaterial(&m_controlsMaterial);
	m_controlsFont.LoadPreset("OCRAExtendedWhite");
	m_controlsFont.SetChromaKeyingOn();

	m_controlsOverlay.Init(&m_controlsMaterial, Vektoria::C2dRect(0.8f, 0.05f, 0.1f, 0.9f));
	m_controlsWriting.Init(Vektoria::C2dRect(0.76f, 0.04f, 0.12f, 0.905f), 100, &m_controlsFont);

	m_controlsOverlay.SetLayer (0.1f);

	CGame::GetInstance().getViewport().AddOverlay(&m_controlsOverlay);
	CGame::GetInstance().getViewport().AddWriting(&m_controlsWriting);

	m_controlsWriting.PrintString("Left: A | Right: D | Up: W | Down: S | Turn Left: Q | Turn Right: E | Move Speed: +- | Rot Speed: ,.");
#pragma endregion
}

TrapShooting::~TrapShooting()
{
	delete m_particleWorld;

	delete m_geoBall;
	delete m_materialBall;

	delete m_clayPieceGeo;
	delete m_clayPieceMaterial;

	delete[] m_pigeons.geos;
	delete[] m_pigeons.materials;
	delete[] m_pigeons.pigeons;
}

void TrapShooting::update(float timeDelta)
{
	m_particleWorld->update(timeDelta);
	moveCanon(timeDelta);
	m_score.update(timeDelta);
	m_scoreWriting.PrintF("Current Score: %5.2f\tHighscore: %5.2f\tTime since Hit: %4.2f", m_score.getCurrentScore(), m_score.getHighscore(), m_score.getTimeSinceIncrease());
	checkBalls();

	checkPigeons();

	m_pigeons.spawnTimeDelta += timeDelta;

	if (m_pigeons.spawn && m_pigeons.spawnTimeDelta > 5.0f)
	{
		m_pigeons.spawnTimeDelta = 0.0f;
		createPigeon();
	}
}

void TrapShooting::spawn()
{
	// new Ball
	auto placementBall = new Vektoria::CPlacement();
	m_pCave->AddPlacement(placementBall);

	// Translate to Canon Base
	const auto cp = m_canon.transPlacement->GetPos();
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

	m_score.decrease(2.0);
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

	if (keyboard.KeyDown(DIK_I))
		m_canon.inverted = !m_canon.inverted;

	const auto movementSpeed = m_canon.movementSpeed * timeDelta;
	const auto rotationSpeed = m_canon.rotationSpeed * timeDelta;
	
	Vektoria::CHVector positionalDifference = Vektoria::CHVector(0.0f, 0.0f, 0.0f, 0.0f);
	
	if (keyboard.KeyPressed(DIK_A))
		positionalDifference.x -= 1.0f;

	if (keyboard.KeyPressed(DIK_D))
		positionalDifference.x += 1.0f;

	Vektoria::CHVector rotationAxis = Vektoria::CHVector(0.0f, 0.0f, 0.0f, 0.0f);

	if (keyboard.KeyPressed(DIK_W))
		rotationAxis.x += m_canon.inverted ? -1.0 : 1.0f;

	if (keyboard.KeyPressed(DIK_S))
		rotationAxis.x += m_canon.inverted ? 1.0f : -1.0f;

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

		m_pCave->SubPlacement((*firstBall)->getPlacement());
		(*firstBall)->getPlacement()->SwitchOff();
		(*firstBall)->destroy();
		m_balls.erase(firstBall);
	}
}

void TrapShooting::checkPigeons()
{
	for (const auto ball : m_balls)
	{
		const auto& position = ball->getParticle()->getPosition();

		if (position.z() > 0.0f
			|| position.x() < 0.0f || position.x() > m_caveDimensions.width
			|| position.y() > m_caveDimensions.height)
			continue;

		for (std::size_t i = 0; i < m_pigeons.count; ++i)
		{
			if (!m_pigeons.pigeons[i]) continue;

			const auto distanceSq = (position - m_pigeons.pigeons[i]->getParticle()->getPosition()).LengthSq();
			auto radiusSum = m_ballRadius + m_pigeons.pigeons[i]->getRadius();

			if (distanceSq <= radiusSum * radiusSum)
			{
				const auto velocityMultiplier = m_pigeons.pigeons[i]->getParticle()->getVelocity().Length() / 5.0f;
				const auto sizeMultiplier = 1.0f / m_pigeons.pigeons[i]->getRadius();
				m_score.increase(velocityMultiplier * sizeMultiplier);

				// Destroy Pigeon
				m_pCave->SubPlacement(m_pigeons.pigeons[i]->getPlacement());
				m_pigeons.pigeons[i]->kill();
				m_pigeons.pigeons[i] = nullptr;

				--m_pigeons.currentCount;
				m_pigeons.spawn = true;
			}
		}

		if (m_mockingbird)
		{
			if (m_mockingbird->isAlive())
			{
				const auto distanceSq = (position - m_mockingbird->getParticle()->getPosition()).LengthSq();
				auto radiusSum = m_ballRadius + m_mockingbird->getRadius();

				if (distanceSq <= radiusSum * radiusSum)
				{
					const auto velocityMultiplier = 0.1f + m_mockingbird->getParticle()->getVelocity().Length();

					m_score.increase(velocityMultiplier);

					m_mockingbird->kill();
				}
			}
		}
	}
}

void TrapShooting::createPigeon()
{
	unsigned int i = 0;
	for (; i < m_pigeons.count; ++i)
		if (!m_pigeons.pigeons[i])
			break;

	if (i == m_pigeons.count) return;

	auto placement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(placement);

	float radius = Todes::Random::Float(0.4f, 1.0f);
	placement->TranslateDelta(convertVector(Todes::Random::Vec3D(Todes::Vector3D(m_caveDimensions.thickness + radius, 10.0f, -m_caveDimensions.depth + m_caveDimensions.thickness + radius), Todes::Vector3D(m_caveDimensions.width - m_caveDimensions.thickness - radius, 20.0f, -m_caveDimensions.thickness - radius))));

	auto pigeon = new ClayPigeon(placement, radius, this, m_pigeons.geos[i], m_pigeons.materials[i]);
	m_particleWorld->addPlacementParticle(pigeon);
	m_pigeons.pigeons[i] = pigeon;

	auto velocity = Todes::Random::Float(1.5f, 5.5f);
	auto force = Todes::Random::Vec3D(1.0f);
	force.y(0.0f);
	force.Normalize();
	force *= velocity;

	pigeon->getParticle()->setVelocity(force);

	if (++m_pigeons.currentCount == m_pigeons.count) m_pigeons.spawn = false;
}

void TrapShooting::registerClayPiece(ClayPiece* piece)
{
	m_pCave->AddPlacement(piece->getPlacement());
	piece->setGeo(m_clayPieceGeo);
	m_particleWorld->addPlacementParticle(piece, { m_gravity });
}
