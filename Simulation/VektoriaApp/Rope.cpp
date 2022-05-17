#include "pch.h"
#include "Rope.h"
#include "ParticleCable.h"
#include "Particle.h"
#include "TodesConverter.h"

Rope::Rope(Vektoria::CPlacement* placement, Vektoria::CGeo* geo, Vektoria::CMaterial* material, Todes::Particle* particle)
	: PlacementParticle(placement, geo, material, particle)
	, m_ropeContact(new Todes::ParticleCable())
{ }

Rope::Rope(Vektoria::CPlacement* placement, Todes::Particle* particle)
	: PlacementParticle(placement, particle)
	, m_ropeContact(new Todes::ParticleCable())
{ }

Rope::Rope(Vektoria::CPlacement* placement, Vektoria::CGeo* geo, Vektoria::CMaterial* material, const float& particleDamping, const float& inverseParticleMass)
	: PlacementParticle(placement, geo, material, particleDamping, inverseParticleMass)
	, m_ropeContact(new Todes::ParticleCable())
{ }

Rope::Rope(Vektoria::CPlacement* placement, const float& particleDamping, const float& inverseParticleMass)
	: PlacementParticle(placement, particleDamping, inverseParticleMass)
	, m_ropeContact(new Todes::ParticleCable())
{ }

Rope::~Rope()
{
	m_placement->SubPlacement(&m_ropePlacement);
}

void Rope::Init(Vektoria::CPlacement* anchorPlacement, const float& ropeLength, const float& ropeRadius /*= 0.1f*/, const float& restitution /*= 0.5f*/)
{
	m_anchorPlacement = anchorPlacement;

	m_ropeMaterial.LoadPreset((char*)"SnakeBot");

	InitContact(ropeLength, restitution);

	InitRope(ropeRadius, ropeLength);
}

void Rope::Init(Vektoria::CPlacement* anchorPlacement, const Vektoria::CMaterial& ropeMaterial, const float& ropeLength, const float& ropeRadius /*= 0.1f*/, const float& restitution /*= 0.5f*/)
{
	m_anchorPlacement = anchorPlacement;
	m_ropeMaterial = ropeMaterial;

	InitContact(ropeLength, restitution);

	InitRope(ropeRadius, ropeLength);
}

void Rope::InitContact(const float& ropeLength, const float& restitution)
{
	auto anchor = new Todes::Particle(convertVector(m_anchorPlacement->GetPos()), 1.0f, 0.0f);
	m_ropeContact->setParticles(m_particle, anchor);
	m_ropeContact->setRestitution(restitution);
	m_ropeContact->setTriggerDistance(ropeLength);
}

void Rope::InitRope(const float& ropeRadius, const float& ropeLength)
{
	m_ropeGeo.Init(ropeRadius, ropeRadius, ropeLength, &m_ropeMaterial);

	m_ropePlacement.AddGeo(&m_ropeGeo);
	m_ropePlacement.SetPointing(m_anchorPlacement);

	m_placement->AddPlacement(&m_ropePlacement);
}

Todes::IParticleContactGenerator* Rope::getContactGenerator()
{
	return m_ropeContact;
}

void Rope::update()
{
	PlacementParticle::update();
}
