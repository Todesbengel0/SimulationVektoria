#include "pch.h"
#include "PendulumScene.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "PlacementParticle.h"
#include "PlacementParticleWorld.h"
#include "ParticleCable.h"
#include "ParticleSpring.h"
#include "ParticleCollision.h"

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
	auto cabulumPosition = Todes::Vector3D(0.0f, -cabulumLength, 0.0f);
	cabulumPosition.RotateZ(-UM_DEG2RAD(30.0f));
	cabulumPosition += convertVector(cabulumAnchorPosition);

	// Translate Particle
	cabulumPlacement->TranslateDelta(convertVector(cabulumPosition));
	m_pCave->AddPlacement(cabulumPlacement);

	// Create Material, Geo and Placement Particle
	auto cabulumMaterial = new Vektoria::CMaterial();
	cabulumMaterial->LoadPreset((char*)"RubberBlack");
	regMaterial(cabulumMaterial);
	auto cabulumGeo = new Vektoria::CGeoSphere();
	cabulumGeo->Init(0.5f, cabulumMaterial);
	auto cabulum = new PlacementParticle(cabulumPlacement, cabulumGeo, cabulumMaterial, 0.999f, 2.0f);

	// Create anchor particle
	auto cabulumAnchor = new Todes::Particle
	(convertVector(cabulumAnchorPosition)
		, 0.999f
		, 0.0f);

	// Create Cable Contact
	auto cabulumCable = new Todes::ParticleCable
		(cabulumLength, 0.5f);
	cabulumCable->setParticles(cabulum->getParticle(), cabulumAnchor);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(cabulum);
	m_particleWorld->addContacts({ cabulumCable });
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

	// Create Material, Geo and Placement Particle
	auto linkulumMaterial = new Vektoria::CMaterial();
	linkulumMaterial->LoadPreset((char*)"BarkBirch");
	regMaterial(linkulumMaterial);
	auto linkulumGeo = new Vektoria::CGeoSphere();
	linkulumGeo->Init(0.4f, linkulumMaterial);
	auto linkulum1 = new PlacementParticle(linkulum1Placement, linkulumGeo, linkulumMaterial, 0.999f, 1.5f);
	auto linkulum2 = new PlacementParticle(linkulum2Placement, linkulumGeo, linkulumMaterial, 0.999f, 1.5f);

	// Create anchor particles
	auto linkulum1Anchor = new Todes::Particle
		(convertVector(linkulum1AnchorPosition)
		, 0.999f
		, 0.0f);
	auto linkulum2Anchor = new Todes::Particle
		(Todes::Vector3D
			(linkulum1AnchorPosition.x + linkulumDistance,
			linkulum1AnchorPosition.y,
			linkulum1AnchorPosition.z)
		, 0.999f
		, 0.0f);

	// Create Cable Contacts
	auto linkulum1Cable = new Todes::ParticleCable
	(linkulumLength, 0.5f);
	linkulum1Cable->setParticles(linkulum1->getParticle(), linkulum1Anchor);
	auto linkulum2Cable = new Todes::ParticleCable
	(linkulumLength, 0.5f);
	linkulum2Cable->setParticles(linkulum2->getParticle(), linkulum2Anchor);

	// Add Spring between linked particles
	m_linkulum1Spring =
		new Todes::ParticleSpring(linkulum2->getParticle(), 5.0f, linkulumRestLength);
	m_linkulum2Spring =
		new Todes::ParticleSpring(linkulum1->getParticle(), 5.0f, linkulumRestLength);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(linkulum1, { m_linkulum1Spring });
	m_particleWorld->addPlacementParticle(linkulum2, { m_linkulum2Spring });
	m_particleWorld->addContacts({ linkulum1Cable });
	m_particleWorld->addContacts({ linkulum2Cable });
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
	sphere5Position.RotateZ(UM_DEG2RAD(20.0f));
	sphere5Position += Todes::Vector3D(
			centerAnchorPosition.x + sphereRadius * 4.0f
			, centerAnchorPosition.y
			, centerAnchorPosition.z);
	sphere5Placement->TranslateDelta(convertVector(sphere5Position));
	m_pCave->AddPlacement(sphere5Placement);

	// Create Material, Geo and Placement Particle
	auto sphereMaterial = new Vektoria::CMaterial();
	sphereMaterial->LoadPreset((char*)"GlassButzen");
	regMaterial(sphereMaterial);
	auto sphereGeo = new Vektoria::CGeoSphere();
	sphereGeo->Init(1.5f, sphereMaterial);
	auto sphere1 = new PlacementParticle(sphere1Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere2 = new PlacementParticle(sphere2Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere3 = new PlacementParticle(sphere3Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere4 = new PlacementParticle(sphere4Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);
	auto sphere5 = new PlacementParticle(sphere5Placement, sphereGeo, sphereMaterial, 0.999f, 0.5f);

	// Create anchor particles
	auto sphere1Anchor = new Todes::Particle
	(Todes::Vector3D
	(centerAnchorPosition.x - sphereRadius * 4.0f,
		centerAnchorPosition.y,
		centerAnchorPosition.z)
		, 0.999f
		, 0.0f);
	auto sphere2Anchor = new Todes::Particle
	(Todes::Vector3D
	(centerAnchorPosition.x - sphereRadius * 2.0f,
		centerAnchorPosition.y,
		centerAnchorPosition.z)
		, 0.999f
		, 0.0f);
	auto sphere3Anchor = new Todes::Particle
	(convertVector(centerAnchorPosition)
		, 0.999f
		, 0.0f);
	auto sphere4Anchor = new Todes::Particle
	(Todes::Vector3D
	(centerAnchorPosition.x + sphereRadius * 2.0f,
		centerAnchorPosition.y,
		centerAnchorPosition.z)
		, 0.999f
		, 0.0f);
	auto sphere5Anchor = new Todes::Particle
	(Todes::Vector3D
	(centerAnchorPosition.x + sphereRadius * 4.0f,
		centerAnchorPosition.y,
		centerAnchorPosition.z)
		, 0.999f
		, 0.0f);

	// Create Cable Contacts
	auto sphere1Cable = new Todes::ParticleCable
	(cableLength, 0.2f);
	sphere1Cable->setParticles(sphere1->getParticle(), sphere1Anchor);
	auto sphere2Cable = new Todes::ParticleCable
	(cableLength, 0.2f);
	sphere2Cable->setParticles(sphere2->getParticle(), sphere2Anchor);
	auto sphere3Cable = new Todes::ParticleCable
	(cableLength, 0.2f);
	sphere3Cable->setParticles(sphere3->getParticle(), sphere3Anchor);
	auto sphere4Cable = new Todes::ParticleCable
	(cableLength, 0.2f);
	sphere4Cable->setParticles(sphere4->getParticle(), sphere4Anchor);
	auto sphere5Cable = new Todes::ParticleCable
	(cableLength, 0.2f);
	sphere5Cable->setParticles(sphere5->getParticle(), sphere5Anchor);

	// Add Placement Particle and Contact
	m_particleWorld->addPlacementParticle(sphere1);
	m_particleWorld->addPlacementParticle(sphere2);
	m_particleWorld->addPlacementParticle(sphere3);
	m_particleWorld->addPlacementParticle(sphere4);
	m_particleWorld->addPlacementParticle(sphere5);
	m_particleWorld->addContacts({ sphere1Cable, sphere2Cable, sphere3Cable, sphere4Cable, sphere5Cable });

	// Create Contact between neighbors
	m_particleWorld->addContacts
	({
		new Todes::ParticleCollision(sphere1->getParticle(), sphere2->getParticle(), sphereRadius * 2.0f, 0.8f),
		new Todes::ParticleCollision(sphere2->getParticle(), sphere3->getParticle(), sphereRadius * 2.0f, 0.8f),
		new Todes::ParticleCollision(sphere3->getParticle(), sphere4->getParticle(), sphereRadius * 2.0f, 0.8f),
		new Todes::ParticleCollision(sphere4->getParticle(), sphere5->getParticle(), sphereRadius * 2.0f, 0.8f)
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
