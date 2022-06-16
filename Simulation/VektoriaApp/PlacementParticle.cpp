#include "pch.h"
#include "PlacementParticle.h"
#include "TodesConverter.h"
#include "Particle.h"

PlacementParticle::PlacementParticle(Vektoria::CPlacement* placement, Vektoria::CGeo* geo, Vektoria::CMaterial* material, Todes::Particle* particle)
	: m_placement(placement),
	m_geo(geo),
	m_material(material),
	m_particle(particle),
	m_dirty(false)
{
	m_placement->AddGeo(m_geo);
}

PlacementParticle::PlacementParticle(Vektoria::CPlacement* placement, Todes::Particle* particle)
	: m_placement(placement),
	m_geo(nullptr),
	m_material(nullptr),
	m_particle(particle),
	m_dirty(false)
{ }

PlacementParticle::PlacementParticle()
	: m_placement(nullptr),
	m_geo(nullptr),
	m_material(nullptr),
	m_particle(nullptr),
	m_dirty(false)
{ }

PlacementParticle::PlacementParticle(Vektoria::CPlacement* placement, Vektoria::CGeo* geo, Vektoria::CMaterial* material, const float& particleDamping, const float& inverseParticleMass)
	: m_placement(placement),
	m_geo(geo),
	m_material(material),
	m_particle(new Todes::Particle(convertVector(m_placement->GetPos()), particleDamping, inverseParticleMass)),
	m_dirty(false)
{
	m_placement->AddGeo(m_geo);
}

PlacementParticle::PlacementParticle(Vektoria::CPlacement* placement, const float& particleDamping, const float& inverseParticleMass)
	: m_placement(placement),
	m_geo(nullptr),
	m_material(nullptr),
	m_particle(new Todes::Particle(convertVector(m_placement->GetPos()), particleDamping, inverseParticleMass)),
	m_dirty(false)
{ }

PlacementParticle::~PlacementParticle()
{ }

void PlacementParticle::update()
{
	auto pos = convertVector(m_particle->getPosition());
	m_placement->Translate(pos);
}

void PlacementParticle::update(const float& timeDelta)
{
	update();
}

void PlacementParticle::reset()
{
	m_particle->reset();
	update();
}

void PlacementParticle::kill()
{
	m_particle->sendDeath();
	m_placement->SwitchOff();
}

void PlacementParticle::destroy()
{
	m_dirty = true;
}

void PlacementParticle::revive() const
{
	m_particle->sendDeath(false);
	m_placement->SwitchOn();
}

bool PlacementParticle::isDirty() const
{
	return m_dirty;
}

void PlacementParticle::setParticle(Todes::Particle* particle)
{
	m_particle = particle;
}

Todes::Particle* PlacementParticle::getParticle() const
{
	return m_particle;
}

void PlacementParticle::setPlacement(Vektoria::CPlacement* placement)
{
	m_placement = placement;
}

Vektoria::CPlacement* PlacementParticle::getPlacement() const
{
	return m_placement;
}

void PlacementParticle::setGeo(Vektoria::CGeo* geo)
{
	if (m_geo)
		m_placement->SubGeo(m_geo);
	m_geo = geo;
	m_placement->AddGeo(m_geo);
}

Vektoria::CGeo* PlacementParticle::getGeo() const
{
	return m_geo;
}

void PlacementParticle::setMaterial(Vektoria::CMaterial* material)
{
	m_material = material;
}

Vektoria::CMaterial* PlacementParticle::getMaterial() const
{
	return m_material;
}
