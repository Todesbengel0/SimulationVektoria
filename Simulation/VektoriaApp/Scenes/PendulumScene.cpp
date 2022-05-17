#include "pch.h"
#include "PendulumScene.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "PlacementParticleWorld.h"
#include "ParticleCable.h"
#include "ParticleSpring.h"
#include "ParticleCollision.h"
#include "Rope.h"

PendulumScene::PendulumScene()
	: CaveScene(-9.807f, 10.0f, 50.0f, 30.0f),
	m_particleWorld(new PlacementParticleWorld)
{
#pragma region Exercise 8.1
	// Create Cabulum Placement
	auto cabulumPlacement = new Vektoria::CPlacement();

	// Calculate Anchor Position
	auto cabulumAnchorPosition = Vektoria::CHVector (
			m_caveDimensions.width * 0.2f,
			m_caveDimensions.height,
			-m_caveDimensions.depth * 0.8f);

	// Calculate Length of the Cable
	auto cabulumLength = m_caveDimensions.height * 0.3f + 0.5f;

	// Calculate Position of Particle
	auto cabulumPosition = Todes::Vector3D(0.0f, -1.0f, 0.0f);
	cabulumPosition.RotateZ(UM_DEG2RAD(-30.0f));
	cabulumPosition *= cabulumLength;
	cabulumPosition += convertVector(cabulumAnchorPosition);

	// Translate Particle
	cabulumPlacement->TranslateDelta(convertVector(cabulumPosition));
	m_pCave->AddPlacement(cabulumPlacement);

	// Create Material and Geo
	auto cabulumMaterial = new Vektoria::CMaterial();
	cabulumMaterial->LoadPreset((char*)"RubberBlack");
	regMaterial(cabulumMaterial);
	auto cabulumGeo = new Vektoria::CGeoSphere();
	cabulumGeo->Init(0.5f, cabulumMaterial);

	// Create Rope Placement Particle
	auto cabulum = new Rope(cabulumPlacement, cabulumGeo, cabulumMaterial, 0.999f, 2.0f);
	cabulum->Init(this, convertVector(cabulumAnchorPosition), cabulumLength);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(cabulum);
	m_particleWorld->addContacts({ cabulum->getContactGenerator() });
#pragma endregion

#pragma region Exercise 8.2
	// Create clingy child placement
	auto clingyChildPlacement = new Vektoria::CPlacement();

	// Calculate distance between child and cabulum
	float clingyLength = m_caveDimensions.height * 0.1f;

	// And position of clingy child
	auto clingyChildPosition = Vektoria::CHVector
		(cabulumPosition.x(), cabulumPosition.y() - clingyLength, cabulumPosition.z());

	// Translate clingy child
	clingyChildPlacement->TranslateDelta(clingyChildPosition);
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
#pragma endregion

#pragma region Exercise 8.3
	// Create linkulum Placement 1 and 2
	auto linkulum1Placement = new Vektoria::CPlacement();
	auto linkulum2Placement = new Vektoria::CPlacement();

	// Calculate Anchor Position
	auto linkulum1AnchorPosition = Vektoria::CHVector(
		m_caveDimensions.width * 0.7f,
		m_caveDimensions.height,
		-m_caveDimensions.depth * 0.5f);

	// Calculate Length of the Cable
	auto linkulumLength = m_caveDimensions.height * 0.4f +0.4f;
	auto linkulumDistance = m_caveDimensions.width * 0.1f;

	// Calculate Position of Particle1
	auto linkulum1Position = Todes::Vector3D(0.0f, -linkulumLength, 0.0f);
	linkulum1Position.RotateZ(UM_DEG2RAD(10.0f));
	linkulum1Position += convertVector(linkulum1AnchorPosition);

	// Calculate Position of Particle2
	auto linkulum2Position = Todes::Vector3D(0.0f, -linkulumLength, 0.0f);
	linkulum2Position.RotateZ(UM_DEG2RAD(15.0f));
	linkulum2Position += Todes::Vector3D(
		linkulum1AnchorPosition.x + linkulumDistance,
		linkulum1AnchorPosition.y,
		linkulum1AnchorPosition.z);
	
	auto linkulumRestLength = (linkulum1Position - linkulum2Position).Length();

	// Translate Particles
	linkulum1Placement->TranslateDelta(convertVector(linkulum1Position));
	linkulum2Placement->TranslateDelta(convertVector(linkulum2Position));
	m_pCave->AddPlacement(linkulum1Placement);
	m_pCave->AddPlacement(linkulum2Placement);

	// Create Material and Geo
	auto linkulumMaterial = new Vektoria::CMaterial();
	linkulumMaterial->LoadPreset((char*)"BarkBirch");
	regMaterial(linkulumMaterial);
	auto linkulumGeo = new Vektoria::CGeoSphere();
	linkulumGeo->Init(0.4f, linkulumMaterial);

	// Create Rope Placement Particles
	auto linkulum1 = new Rope(linkulum1Placement, linkulumGeo, linkulumMaterial, 0.999f, 1.5f);
	auto linkulum2 = new Rope(linkulum2Placement, linkulumGeo, linkulumMaterial, 0.999f, 1.5f);
	linkulum1->Init(this, convertVector(linkulum1AnchorPosition), linkulumLength, 0.05f);
	linkulum2->Init(this, Todes::Vector3D
		( linkulum1AnchorPosition.x + linkulumDistance
		, linkulum1AnchorPosition.y
		, linkulum1AnchorPosition.z), linkulumLength, 0.05f);

	// Add Spring between linked particles
	m_linkulum1Spring =
		new Todes::ParticleSpring(linkulum2->getParticle(), 5.0f, linkulumRestLength);
	m_linkulum2Spring =
		new Todes::ParticleSpring(linkulum1->getParticle(), 5.0f, linkulumRestLength);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(linkulum1, { m_linkulum1Spring });
	m_particleWorld->addPlacementParticle(linkulum2, { m_linkulum2Spring });
	m_particleWorld->addContacts({ linkulum1->getContactGenerator() });
	m_particleWorld->addContacts({ linkulum2->getContactGenerator() });
#pragma endregion

#pragma region Exercise 8.4
	const auto sphereRadius = 1.5f;
	
	// Create placements
	auto sphere1Placement = new Vektoria::CPlacement();
	auto sphere2Placement = new Vektoria::CPlacement();
	auto sphere3Placement = new Vektoria::CPlacement();
	auto sphere4Placement = new Vektoria::CPlacement();
	auto sphere5Placement = new Vektoria::CPlacement();

	// Create center anchor position
	auto centerAnchorPosition = Vektoria::CHVector(
		m_caveDimensions.width * 0.5f,
		m_caveDimensions.height,
		-m_caveDimensions.depth * 0.2f);

	// Cable Length
	auto cableLength = m_caveDimensions.height * 0.8f - sphereRadius;

	// Calculate Position of Particle1
	auto sphere1Position =
		Vektoria::CHVector(centerAnchorPosition.x - sphereRadius * 4.0f
						, centerAnchorPosition.y - cableLength
						, centerAnchorPosition.z);
	sphere1Placement->TranslateDelta(sphere1Position);
	m_pCave->AddPlacement(sphere1Placement);

	// Calculate Position of Particle2
	auto sphere2Position =
		Vektoria::CHVector(centerAnchorPosition.x - sphereRadius * 2.0f
						, centerAnchorPosition.y - cableLength
						, centerAnchorPosition.z);
	sphere2Placement->TranslateDelta(sphere2Position);
	m_pCave->AddPlacement(sphere2Placement);

	// Calculate Position of Particle3
	auto sphere3Position =
		Vektoria::CHVector(centerAnchorPosition.x
			, centerAnchorPosition.y - cableLength
			, centerAnchorPosition.z);
	sphere3Placement->TranslateDelta(sphere3Position);
	m_pCave->AddPlacement(sphere3Placement);

	// Calculate Position of Particle4
	auto sphere4Position =
		Vektoria::CHVector(centerAnchorPosition.x + sphereRadius * 2.0f
			, centerAnchorPosition.y - cableLength
			, centerAnchorPosition.z);
	sphere4Placement->TranslateDelta(sphere4Position);
	m_pCave->AddPlacement(sphere4Placement);

	// Calculate Position of Particle5
	auto sphere5Position = Todes::Vector3D(0.0f, -cableLength-sphereRadius, 0.0f);
	sphere5Position.RotateZ(UM_DEG2RAD(40.0f));
	sphere5Position += Todes::Vector3D(
			centerAnchorPosition.x + sphereRadius * 4.0f
			, centerAnchorPosition.y
			, centerAnchorPosition.z);
	sphere5Placement->TranslateDelta(convertVector(sphere5Position));
	m_pCave->AddPlacement(sphere5Placement);

	// Create Material, Geo and Placement Particle
	auto sphereMaterial = new Vektoria::CMaterial();
	sphereMaterial->LoadPreset((char*)"GlassButzen");
	sphereMaterial->SetTransparency(0.2f);
	regMaterial(sphereMaterial);
	auto sphereGeo = new Vektoria::CGeoSphere();
	sphereGeo->Init(1.5f, sphereMaterial);
	auto sphere1 = new Rope(sphere1Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere2 = new Rope(sphere2Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere3 = new Rope(sphere3Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere4 = new Rope(sphere4Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere5 = new Rope(sphere5Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);

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
		new Todes::ParticleCollision(sphere1->getParticle(), sphere2->getParticle(), sphereRadius * 2.0f, 0.9f),
		new Todes::ParticleCollision(sphere2->getParticle(), sphere3->getParticle(), sphereRadius * 2.0f, 0.9f),
		new Todes::ParticleCollision(sphere3->getParticle(), sphere4->getParticle(), sphereRadius * 2.0f, 0.9f),
		new Todes::ParticleCollision(sphere4->getParticle(), sphere5->getParticle(), sphereRadius * 2.0f, 0.9f)
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
