#include "pch.h"
#include "ClayPiece.h"
#include "Particle.h"

ClayPiece::ClayPiece(Vektoria::CPlacement* placement, const CaveDimensions& bounds, const float& radius, const float& inverseMass)
	: PlacementParticle(placement, 0.999f, inverseMass)
	, m_bounds(bounds)
	, m_radius(radius)
{
	m_geoPlacement = new Vektoria::CPlacement();
	m_placement->AddPlacement(m_geoPlacement);
	m_geoPlacement->Scale(m_radius);
}

void ClayPiece::update()
{
	if (m_particle->isDead())
		return;

	PlacementParticle::update();

	const auto position = m_placement->GetPos();

	if (position.y - m_radius < m_bounds.thickness)
	{
		m_placement->TranslateY((m_radius + m_bounds.thickness) - position.y);
		kill();
		return;
	}

	if (position.z + m_radius > -m_bounds.thickness || position.z - m_radius < -m_bounds.depth + m_bounds.thickness
		|| position.x - m_radius < m_bounds.thickness || position.x + m_radius > m_bounds.width - m_bounds.thickness)
		m_particle->setVelocity(Todes::Vector3D(0.0f, m_particle->getVelocity().y(), 0.0f));
}

void ClayPiece::kill()
{
	m_particle->sendDeath();
}

void ClayPiece::reset()
{}

void ClayPiece::revive() const
{}

void ClayPiece::setGeo(Vektoria::CGeo* geo)
{
	if (m_geo)
		m_geoPlacement->SubGeo(m_geo);
	m_geo = geo;
	m_geoPlacement->AddGeo(m_geo);
}
