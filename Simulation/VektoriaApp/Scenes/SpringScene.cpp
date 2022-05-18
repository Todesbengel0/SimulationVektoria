#include "pch.h"
#include "SpringScene.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "ParticleSpring.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleAnchoredBungee.h"
#include "ParticleFloatage.h"
#include "Game.h"

SpringScene::SpringScene()
	: CaveScene(-9.807f, 10.0f, 50.0f, 30.0f),
	m_particleWorld(new PlacementParticleWorld)
{
//	setWASDCam(false);

	// Player Character
	auto playerPlacement = new Vektoria::CPlacement();
	playerPlacement->TranslateDelta(m_pCave->GetPos());
	playerPlacement->TranslateDelta(Vektoria::CHVector(m_caveDimensions.width * 0.5f, 1.5f, -m_caveDimensions.depth * 0.5f));
	AddPlacement(playerPlacement);
	auto playerMaterial = new Vektoria::CMaterial();
	playerMaterial->LoadPreset((char*)"Lemon");
	regMaterial(playerMaterial);
	auto playerGeo = new Vektoria::CGeoSphere();
	playerGeo->Init(1.5f, playerMaterial);

//	m_cameraPlacement.SetPointing(playerPlacement);

	m_player = new PlacementParticle(playerPlacement, playerGeo, playerMaterial, 0.999f, 1.0f);
	m_particleWorld->addPlacementParticle(m_player);

	// Create Particle and Force for Camera
// 	auto camera = new PlacementParticle(&m_cameraPlacement, 0.999f, 1.0f);
// 	auto playerCameraVector = playerPlacement->GetPos() - m_cameraPlacement.GetPos();
// 	auto restLength = playerCameraVector.Length();
// 	auto cameraPlayerSpring = new Todes::ParticleSpring(m_player->getParticle(), 0.2f, restLength);
// 	m_particleWorld->addPlacementParticle(camera, { cameraPlayerSpring });

	// Create Bungee jumper
	auto jumperPlacement = new Vektoria::CPlacement();
	jumperPlacement->TranslateDelta(Vektoria::CHVector(m_caveDimensions.width * 0.2f, m_caveDimensions.height * 0.8f, -m_caveDimensions.depth * 0.5f));
	m_pCave->AddPlacement(jumperPlacement);
	auto jumperMaterial = new Vektoria::CMaterial();
	jumperMaterial->LoadPreset((char*)"SkinElephant");
	regMaterial(jumperMaterial);
	auto jumperGeo = new Vektoria::CGeoSphere();
	jumperGeo->Init(1.0f, jumperMaterial);
	auto jumper = new PlacementParticle(jumperPlacement, jumperGeo, jumperMaterial, 0.999f, 1.5f);
	auto jumperRestLength = m_caveDimensions.height * 0.5f;
	auto jumperBungee = new Todes::ParticleAnchoredBungee(convertVector(jumperPlacement->GetPos()), 10.0f, jumperRestLength);
	m_particleWorld->addPlacementParticle(jumper, { m_gravity, jumperBungee });

	// Create Water Tank
	auto waterTank = new Vektoria::CPlacement();
	m_pCave->AddPlacement(waterTank);
	waterTank->TranslateDelta(Vektoria::CHVector(m_caveDimensions.width * 0.8f, m_caveDimensions.height * 0.15f, -m_caveDimensions.depth * 0.5f));
	auto tankMaterial = new Vektoria::CMaterial();
	tankMaterial->LoadPreset((char*)"Water");
	tankMaterial->SetTransparency(0.2f);
	regMaterial(tankMaterial);
	auto tankGeo = new Vektoria::CGeoCube();
	auto tankWidth = m_caveDimensions.width * 0.15f;
	auto tankHeight = m_caveDimensions.height * 0.15f;
	auto tankDepth = m_caveDimensions.depth * 0.3f;
	tankGeo->Init(Vektoria::CHVector(tankWidth, tankHeight, tankDepth), tankMaterial);
	waterTank->AddGeo(tankGeo);

	// Create Swimmer
	auto swimmerPlacement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(swimmerPlacement);
	swimmerPlacement->TranslateDelta(waterTank->GetPos());
	swimmerPlacement->TranslateYDelta(m_caveDimensions.height);
	auto swimmerMaterial = new Vektoria::CMaterial();
	swimmerMaterial->LoadPreset((char*)"PhongGreen");
	regMaterial(swimmerMaterial);
	auto swimmerGeo = new Vektoria::CGeoSphere();
	swimmerGeo->Init(1.0f, swimmerMaterial);
	auto swimmer = new PlacementParticle(swimmerPlacement, swimmerGeo, swimmerMaterial, 0.999f, 0.005f);
	auto swimmerFloatage = new Todes::ParticleFloatage(1.0f, waterTank->GetPos().y + tankHeight);
	m_particleWorld->addPlacementParticle(swimmer, { m_gravity, swimmerFloatage });
}

SpringScene::~SpringScene()
{
	delete m_particleWorld;
}

void SpringScene::update(float timeDelta)
{
	move(m_player, timeDelta);

	m_particleWorld->update(timeDelta);
}

void SpringScene::move(PlacementParticle* actor, const float& timeDelta)
{
	const auto movementSpeed = 10.0f * timeDelta;
	auto& keyboard = CGame::GetInstance().getKeyboard();
	Todes::Vector3D positionalDifference;

	if (keyboard.KeyPressed(DIK_W))
		positionalDifference += Todes::Vector3D(0.0f, 0.0f, -1.0f);

	if (keyboard.KeyPressed(DIK_A))
		positionalDifference += Todes::Vector3D(-1.0f, 0.0f, 0.0f);

	if (keyboard.KeyPressed(DIK_S))
		positionalDifference += Todes::Vector3D(0.0f, 0.0f, 1.0f);

	if (keyboard.KeyPressed(DIK_D))
		positionalDifference += Todes::Vector3D(1.0f, 0.0f, 0.0f);

	if (positionalDifference.LengthSq() == 0.0f)
		return;

	actor->getParticle()->translate(positionalDifference.Normalize() * movementSpeed);
	actor->update();
}

void SpringScene::reset()
{
	m_particleWorld->reset();
}

void SpringScene::spawn()
{

}
