#include "pch.h"
#include "Pendulum.h"
#include "ParticleCable.h"
#include "Particle.h"
#include "TodesConverter.h"
#include "Scenes/CaveScene.h"

Pendulum::Pendulum(Vektoria::CPlacement* placement, Vektoria::CGeo* geo, Vektoria::CMaterial* material, Todes::Particle* particle)
	: PlacementParticle(placement, geo, material, particle)
	, m_ropeContact(new Todes::ParticleCable())
{ }

Pendulum::Pendulum(Vektoria::CPlacement* placement, Todes::Particle* particle)
	: PlacementParticle(placement, particle)
	, m_ropeContact(new Todes::ParticleCable())
{ }

Pendulum::Pendulum(Vektoria::CPlacement* placement, Vektoria::CGeo* geo, Vektoria::CMaterial* material, const float& particleDamping, const float& inverseParticleMass)
	: PlacementParticle(placement, geo, material, particleDamping, inverseParticleMass)
	, m_ropeContact(new Todes::ParticleCable())
{ }

Pendulum::Pendulum(Vektoria::CPlacement* placement, const float& particleDamping, const float& inverseParticleMass)
	: PlacementParticle(placement, particleDamping, inverseParticleMass)
	, m_ropeContact(new Todes::ParticleCable())
{ }

Pendulum::~Pendulum()
{
	delete m_anchorPlacement;
}

void Pendulum::Init(CaveScene* scene, const Todes::Vector3D& anchorPosition, const float& ropeLength, const float& ropeRadius /*= 0.1f*/, const float& restitution /*= 0.5f*/)
{	
	m_anchorPlacement = new Vektoria::CPlacement();
	m_anchorPlacement->TranslateDelta(convertVector(anchorPosition));
	scene->getCave()->AddPlacement(m_anchorPlacement);

	InitMaterial(scene);

	InitContact(anchorPosition, ropeLength, restitution);

	InitRope(ropeRadius, ropeLength);
}

void Pendulum::Init(CaveScene* scene, const Todes::Vector3D& anchorPosition, const Vektoria::CMaterial& ropeMaterial, const float& ropeLength, const float& ropeRadius /*= 0.1f*/, const float& restitution /*= 0.5f*/)
{
	m_anchorPlacement = new Vektoria::CPlacement();
	m_anchorPlacement->TranslateDelta(convertVector(anchorPosition));
	scene->getCave()->AddPlacement(m_anchorPlacement);

	m_ropeMaterial = ropeMaterial;

	InitContact(anchorPosition, ropeLength, restitution);

	InitRope(ropeRadius, ropeLength);
}

void Pendulum::Init(CaveScene* scene, PlacementParticle* anchorPlacementParticle, const float& ropeLength, const float& ropeRadius /*= 0.1f */, const float& restitution /*= 0.3f*/)
{
	m_anchorPlacement = anchorPlacementParticle->getPlacement();

	InitMaterial(scene);

	InitContact(anchorPlacementParticle->getParticle(), ropeLength, restitution);

	InitRope(ropeRadius, ropeLength);
}

void Pendulum::Init(CaveScene* scene, PlacementParticle* anchorPlacementParticle, const Vektoria::CMaterial& ropeMaterial, const float& ropeLength, const float& ropeRadius /*= 0.1f */, const float& restitution /*= 0.3f*/)
{
	m_anchorPlacement = anchorPlacementParticle->getPlacement();

	m_ropeMaterial = ropeMaterial;

	InitContact(anchorPlacementParticle->getParticle(), ropeLength, restitution);

	InitRope(ropeRadius, ropeLength);
}

void Pendulum::InitMaterial(CaveScene* scene)
{
	m_ropeMaterial.LoadPreset((char*)"PhongYellow");
	scene->regMaterial(&m_ropeMaterial);
}

void Pendulum::InitContact(const Todes::Vector3D& anchorPosition, const float& ropeLength, const float& restitution)
{
	auto anchor = new Todes::Particle(anchorPosition, 1.0f, 0.0f);
	m_ropeContact->setParticles(m_particle, anchor);
	m_ropeContact->setRestitution(restitution);
	m_ropeContact->setTriggerDistance(ropeLength);
}

void Pendulum::InitContact(Todes::Particle* anchorParticle, const float& ropeLength, const float& restitution)
{
	m_ropeContact->setParticles(m_particle, anchorParticle);
	m_ropeContact->setRestitution(restitution);
	m_ropeContact->setTriggerDistance(ropeLength);
}

void Pendulum::InitRope(const float& ropeRadius, const float& ropeLength)
{
	m_ropeGeo.Init(ropeRadius, ropeRadius, ropeLength, &m_ropeMaterial);

	m_pointingPlacement.AddPlacement(&m_ropePlacement);
	m_ropePlacement.AddGeo(&m_ropeGeo);
	m_ropePlacement.RotateXDelta(-HALFPI);
	m_anchorPlacement->AddPlacement(&m_pointingPlacement);
	m_pointingPlacement.SetPointing(m_placement);
}

Todes::IParticleContactGenerator* Pendulum::getContactGenerator()
{
	return m_ropeContact;
}

void Pendulum::update()
{
	PlacementParticle::update();
}
