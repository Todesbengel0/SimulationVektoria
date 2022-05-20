#include "pch.h"
#include "PendulumScene.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "PlacementParticleWorld.h"
#include "ParticleCable.h"
#include "ParticleSpring.h"
#include "ParticleCollision.h"
#include "Pendulum.h"

PendulumScene::PendulumScene()
	: CaveScene(-9.807f, 10.0f, 50.0f, 30.0f),
	m_particleWorld(new PlacementParticleWorld)
{
#pragma region Exercise 8.1
	// Calculate Anchor Position
	auto cabulumAnchorPosition = Vektoria::CHVector (
			m_caveDimensions.width * 0.2f,
			m_caveDimensions.height - m_caveDimensions.thickness,
			-m_caveDimensions.depth * 0.8f);

	// Calculate Length of the Cable
	auto cabulumLength = m_caveDimensions.height * 0.3f;

	// Create Cabulum Placement
	auto cabulumPlacement = new Vektoria::CPlacement();
	cabulumPlacement->TranslateYDelta(-cabulumLength);
	cabulumPlacement->RotateZDelta(UM_DEG2RAD(-30.0f));
	cabulumPlacement->TranslateDelta(cabulumAnchorPosition);
	m_pCave->AddPlacement(cabulumPlacement);
	

	// Create Material and Geo
	auto cabulumMaterial = new Vektoria::CMaterial();
	cabulumMaterial->LoadPreset((char*)"RubberBlack");
	regMaterial(cabulumMaterial);
	auto cabulumGeo = new Vektoria::CGeoSphere();
	cabulumGeo->Init(0.5f, cabulumMaterial);

	// Create Pendulum Placement Particle
	auto cabulum = new Pendulum(cabulumPlacement, cabulumGeo, cabulumMaterial, 0.999f, 1.0f);
	cabulum->Init(this, convertVector(cabulumAnchorPosition), cabulumLength);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(cabulum);
	m_particleWorld->addContacts({ cabulum->getContactGenerator() });
#pragma endregion

#pragma region Exercise 8.2
	// Calculate distance between child and cabulum
	float clingyLength = m_caveDimensions.height * 0.1f;

	// Create clingy child placement
	auto clingyChildPlacement = new Vektoria::CPlacement();
	clingyChildPlacement->TranslateDelta(cabulumPlacement->GetPos());
	clingyChildPlacement->TranslateYDelta(-clingyLength);
	m_pCave->AddPlacement(clingyChildPlacement);

	// Create Material, Geo and Placement Particle
	auto clingyChildMaterial = new Vektoria::CMaterial();
	clingyChildMaterial->LoadPreset((char*)"Blood");
	regMaterial(clingyChildMaterial);
	auto clingyChildGeo = new Vektoria::CGeoSphere();
	clingyChildGeo->Init(0.3f, clingyChildMaterial);
	auto clingyChild = new PlacementParticle(clingyChildPlacement, clingyChildGeo, clingyChildMaterial, 0.999f, 4.0f);
	
	// Add Spring between child and cabulum
	auto cabulumSpring = new Todes::ParticleSpring(cabulum->getParticle(), 5.0f, clingyLength);
	m_particleWorld->addPlacementParticle(clingyChild, { cabulumSpring });
//	auto cabulumSpring1 = new Todes::ParticleSpring(clingyChild->getParticle(), 5.0f, clingyLength);
//	m_particleWorld->addPlacementParticle(cabulum, { cabulumSpring1 });
#pragma endregion

#pragma region Double_Pendulum
	// Calculate distance between doubulum and cabulum
	float doubulumLength = m_caveDimensions.height * 0.25f;

	// Create doubulum placement
	auto doubulumPlacement = new Vektoria::CPlacement();
	doubulumPlacement->TranslateYDelta(-doubulumLength);
	doubulumPlacement->RotateZDelta(UM_DEG2RAD(-45.0f));
	doubulumPlacement->TranslateDelta(cabulumPlacement->GetPos());
	m_pCave->AddPlacement(doubulumPlacement);
	
	// Create Material and Geo
	auto doubulumMaterial = new Vektoria::CMaterial();
	doubulumMaterial->LoadPreset((char*)"MetalAlu");
	regMaterial(doubulumMaterial);
	auto doubulumGeo = new Vektoria::CGeoSphere();
	doubulumGeo->Init(0.15f, doubulumMaterial);

	// Create doubulum Placement Particles
	auto doubulum = new Pendulum(doubulumPlacement, doubulumGeo, doubulumMaterial, 0.999f, 20.0f);
	doubulum->Init(this, cabulum, doubulumLength, 0.02f, 1.0f);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(doubulum);
	m_particleWorld->addContacts({ doubulum->getContactGenerator() });
#pragma endregion

#pragma region Exercise 8.3
	// Calculate Anchor Position
	auto linkulum1AnchorPosition = Vektoria::CHVector(
		m_caveDimensions.width * 0.7f,
		m_caveDimensions.height - m_caveDimensions.thickness,
		-m_caveDimensions.depth * 0.5f);

	// Calculate Length of the Cable
	auto linkulumLength = m_caveDimensions.height * 0.4f;
	auto linkulumDistance = m_caveDimensions.width * 0.1f;

	// Create Placement of Particle1
	auto linkulum1Placement = new Vektoria::CPlacement();
	linkulum1Placement->TranslateYDelta(-linkulumLength);
	linkulum1Placement->RotateZDelta(UM_DEG2RAD(10.0f));
	linkulum1Placement->TranslateDelta(linkulum1AnchorPosition);
	m_pCave->AddPlacement(linkulum1Placement);

	// Create Placement of Particle2
	auto linkulum2Placement = new Vektoria::CPlacement();
	linkulum2Placement->TranslateYDelta(-linkulumLength);
	linkulum2Placement->RotateZDelta(UM_DEG2RAD(15.0f));
	linkulum2Placement->TranslateDelta(Vektoria::CHVector
		( linkulum1AnchorPosition.x + linkulumDistance
		, linkulum1AnchorPosition.y
		, linkulum1AnchorPosition.z));
	m_pCave->AddPlacement(linkulum2Placement);
	
	auto linkulumRestLength = (linkulum1Placement->GetPos() - linkulum2Placement->GetPos()).Length();

	// Create Material and Geo
	auto linkulumMaterial = new Vektoria::CMaterial();
	linkulumMaterial->LoadPreset((char*)"BarkBirch");
	regMaterial(linkulumMaterial);
	auto linkulumGeo = new Vektoria::CGeoSphere();
	linkulumGeo->Init(0.4f, linkulumMaterial);

	// Create Pendulum Placement Particles
	auto linkulum1 = new Pendulum(linkulum1Placement, linkulumGeo, linkulumMaterial, 0.999f, 1.5f);
	auto linkulum2 = new Pendulum(linkulum2Placement, linkulumGeo, linkulumMaterial, 0.999f, 1.5f);
	linkulum1->Init(this, convertVector(linkulum1AnchorPosition), linkulumLength, 0.05f);
	linkulum2->Init(this, Todes::Vector3D
		( linkulum1AnchorPosition.x + linkulumDistance
		, linkulum1AnchorPosition.y
		, linkulum1AnchorPosition.z), linkulumLength, 0.05f);

	// Add Spring between linked particles
	m_linkulum1Spring =
		new Todes::ParticleSpring(linkulum2->getParticle(), 2.0f, linkulumRestLength);
	m_linkulum2Spring =
		new Todes::ParticleSpring(linkulum1->getParticle(), 2.0f, linkulumRestLength);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(linkulum1, { m_linkulum1Spring });
	m_particleWorld->addPlacementParticle(linkulum2, { m_linkulum2Spring });
	m_particleWorld->addContacts({ linkulum1->getContactGenerator() });
	m_particleWorld->addContacts({ linkulum2->getContactGenerator() });
#pragma endregion

#pragma region Exercise 8.4
	const auto sphereRadius = 1.5f;

	// Create center anchor position
	auto centerAnchorPosition = Vektoria::CHVector(
		m_caveDimensions.width * 0.5f,
		m_caveDimensions.height - m_caveDimensions.thickness,
		-m_caveDimensions.depth * 0.2f);

	// Cable Length
	auto cableLength = m_caveDimensions.height * 0.8f;
	auto sphereHeight = centerAnchorPosition.y - cableLength;

	// Create Placement of Sphere 1
	auto sphere1Placement = new Vektoria::CPlacement();
	sphere1Placement->TranslateYDelta(-cableLength);
	sphere1Placement->RotateZDelta(UM_DEG2RAD(-40.0f));
	sphere1Placement->TranslateDelta(Vektoria::CHVector
			( centerAnchorPosition.x - sphereRadius * 4.0f
			, centerAnchorPosition.y
			, centerAnchorPosition.z));
	m_pCave->AddPlacement(sphere1Placement);

	// Create Placement of Sphere 2
	auto sphere2Placement = new Vektoria::CPlacement();
	sphere2Placement->TranslateDelta(Vektoria::CHVector
			( centerAnchorPosition.x - sphereRadius * 2.0f
			, sphereHeight
			, centerAnchorPosition.z));
	m_pCave->AddPlacement(sphere2Placement);

	// Create Placement of Sphere 3
	auto sphere3Placement = new Vektoria::CPlacement();
	sphere3Placement->TranslateDelta(Vektoria::CHVector
			( centerAnchorPosition.x
			, sphereHeight
			, centerAnchorPosition.z));
	m_pCave->AddPlacement(sphere3Placement);

	// Create Placement of Sphere 4
	auto sphere4Placement = new Vektoria::CPlacement();
	sphere4Placement->TranslateYDelta(-cableLength);
	sphere4Placement->RotateZDelta(UM_DEG2RAD(40.0f));
	sphere4Placement->TranslateDelta(Vektoria::CHVector
			( centerAnchorPosition.x + sphereRadius * 2.0f
			, centerAnchorPosition.y
			, centerAnchorPosition.z));
	m_pCave->AddPlacement(sphere4Placement);

	// Create Placement of Sphere 5
	auto sphere5Placement = new Vektoria::CPlacement();
	sphere5Placement->TranslateYDelta(-cableLength);
	sphere5Placement->RotateZDelta(UM_DEG2RAD(40.0f));
	sphere5Placement->TranslateDelta(Vektoria::CHVector
			( centerAnchorPosition.x + sphereRadius * 4.0f
			, centerAnchorPosition.y
			, centerAnchorPosition.z));
	m_pCave->AddPlacement(sphere5Placement);

	// Create Material, Geo and Placement Particle
	auto sphereMaterial = new Vektoria::CMaterial();
	sphereMaterial->LoadPreset((char*)"GlassButzen");
	sphereMaterial->SetTransparency(0.2f);
	regMaterial(sphereMaterial);
	auto sphereGeo = new Vektoria::CGeoSphere();
	sphereGeo->Init(1.5f, sphereMaterial);
	auto sphere1 = new Pendulum(sphere1Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere2 = new Pendulum(sphere2Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere3 = new Pendulum(sphere3Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere4 = new Pendulum(sphere4Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere5 = new Pendulum(sphere5Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);

	sphere1->Init(this, Todes::Vector3D
		(centerAnchorPosition.x - sphereRadius * 4.0f,
		centerAnchorPosition.y,
		centerAnchorPosition.z), cableLength, 0.2f);

	sphere2->Init(this, Todes::Vector3D
		(centerAnchorPosition.x - sphereRadius * 2.0f,
		centerAnchorPosition.y,
		centerAnchorPosition.z), cableLength, 0.2f);

	sphere3->Init(this, convertVector(centerAnchorPosition), cableLength, 0.2f);

	sphere4->Init(this, Todes::Vector3D
		(centerAnchorPosition.x + sphereRadius * 2.0f,
		centerAnchorPosition.y,
		centerAnchorPosition.z), cableLength, 0.2f);

	sphere5->Init(this, Todes::Vector3D
		(centerAnchorPosition.x + sphereRadius * 4.0f,
		centerAnchorPosition.y,
		centerAnchorPosition.z), cableLength, 0.2f);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(sphere1);
	m_particleWorld->addPlacementParticle(sphere2);
	m_particleWorld->addPlacementParticle(sphere3);
	m_particleWorld->addPlacementParticle(sphere4);
	m_particleWorld->addPlacementParticle(sphere5);
	m_particleWorld->addContacts(
		{ sphere1->getContactGenerator()
		, sphere2->getContactGenerator()
		, sphere3->getContactGenerator()
		, sphere4->getContactGenerator()
		, sphere5->getContactGenerator()});

	// Create Contact between neighbors
	m_particleWorld->addContacts
	({
		new Todes::ParticleCollision(sphere1->getParticle(), sphere2->getParticle(), sphereRadius * 2.0f, 0.95f),
		new Todes::ParticleCollision(sphere2->getParticle(), sphere3->getParticle(), sphereRadius * 2.0f, 0.95f),
		new Todes::ParticleCollision(sphere3->getParticle(), sphere4->getParticle(), sphereRadius * 2.0f, 0.95f),
		new Todes::ParticleCollision(sphere4->getParticle(), sphere5->getParticle(), sphereRadius * 2.0f, 0.95f)
	});
#pragma endregion
}

PendulumScene::~PendulumScene()
{ }

void PendulumScene::update(float timeDelta)
{
	m_particleWorld->update(timeDelta);
}

void PendulumScene::reset()
{
	m_particleWorld->reset();
}

void PendulumScene::spawn()
{
	m_particleWorld->addForces( { m_gravity });
	m_linkulum1Spring->setRestLength(m_linkulum1Spring->getRestLength() - 0.5f);
	m_linkulum2Spring->setRestLength(m_linkulum2Spring->getRestLength() - 0.5f);
}
