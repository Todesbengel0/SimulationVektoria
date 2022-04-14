#include "pch.h"
#include "PlacementParticle.h"
#include "TodesConverter.h"
#include "Particle.h"

PlacementParticle::PlacementParticle(Vektoria::CPlacement* placement, Vektoria::CGeo* geo, Vektoria::CMaterial* material, Particle* particle)
	: m_placement(placement),
	m_geo(geo),
	m_material(material),
	m_particle(particle)
{ }

PlacementParticle::PlacementParticle(Vektoria::CPlacement* placement, Particle* particle)
	: m_placement(placement),
	m_geo(nullptr),
	m_material(nullptr),
	m_particle(particle)
{ }

PlacementParticle::PlacementParticle()
	: m_placement(nullptr),
	m_geo(nullptr),
	m_material(nullptr),
	m_particle(nullptr)
{

}

PlacementParticle::~PlacementParticle()
= default;

void PlacementParticle::update() const
{
	auto pos = convertVector(m_particle->getPosition());
	m_placement->Translate(pos);
}

void PlacementParticle::setParticle(Particle* particle)
{
	m_particle = particle;
}

Particle* PlacementParticle::getParticle() const
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
	m_geo = geo;
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
