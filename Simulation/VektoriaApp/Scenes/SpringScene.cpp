#include "pch.h"
#include "SpringScene.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "ParticleSpring.h"
#include "ParticleAnchoredSpring.h"
#include "Game.h"

SpringScene::SpringScene()
	: CaveScene(-9.807f, 10.0f, 50.0f, 30.0f),
	m_particleWorld(new PlacementParticleWorld)
{
	setWASDCam(false);

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

	m_player = new PlacementParticle(playerPlacement, playerGeo, playerMaterial, 0.999f, 1.0f);
	m_particleWorld->addPlacementParticle(m_player);

	// Create Particle and Force for Camera
	auto camera = new PlacementParticle(&m_cameraPlacement, 0.999f, 1.0f);
	auto playerCameraVector = playerPlacement->GetPos() - m_cameraPlacement.GetPos();
	auto restLength = playerCameraVector.Length();
	auto cameraPlayerSpring = new Todes::ParticleSpring(m_player->getParticle(), 0.2f, restLength);
	m_particleWorld->addPlacementParticle(camera, { cameraPlayerSpring });

	// Create Bungee jumper
	auto jumperPlacement = new Vektoria::CPlacement();
	jumperPlacement->TranslateDelta(Vektoria::CHVector(m_caveDimensions.width * 0.2f, m_caveDimensions.height * 0.8f, -m_caveDimensions.depth * 0.5f));
	m_pCave->AddPlacement(jumperPlacement);
	auto jumperMaterial = new Vektoria::CMaterial();
	jumperMaterial->LoadPreset((char*)"SkinElephant");
	regMaterial(jumperMaterial);
	auto jumperGeo = new Vektoria::CGeoSphere();
	jumperGeo->Init(1.0f, jumperMaterial);
	auto jumper = new PlacementParticle(jumperPlacement, jumperGeo, jumperMaterial, 0.999f, 0.5f);
	auto jumperRestLength = m_caveDimensions.height * 0.4f;
	auto jumperSpring = new Todes::ParticleAnchoredSpring(convertVector(jumperPlacement->GetPos()), 2.0f, jumperRestLength);
	m_particleWorld->addPlacementParticle(jumper, { m_gravity, jumperSpring });
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
