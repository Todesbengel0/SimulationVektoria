#include "pch.h"
#include "ClayPigeon.h"
#include "Scenes/TrapShooting.h"
#include "Particle.h"
#include "Random.h"
#include "PlacementParticleWorld.h"
#include "TodesConverter.h"
#include "ClayPiece.h"

ClayPigeon::ClayPigeon(Vektoria::CPlacement* placement, const float& radius, TrapShooting* scene, Vektoria::CGeo* geo, Vektoria::CMaterial* material)
	: PlacementParticle(placement, 0.999f, 1.0f)
	, m_radius(radius)
	, m_scene(scene)
	, m_payloadBounds{20, 50, 0.05f * radius, 0.2f * radius}
{
	m_geo = geo;
	m_material = material;
	m_geoPlacement = new Vektoria::CPlacement();
	m_placement->AddPlacement(m_geoPlacement);
	m_geoPlacement->AddGeo(m_geo);
	m_geoPlacement->Scale(radius);
}

void ClayPigeon::update(const float& timeDelta)
{
	update();
}

void ClayPigeon::update()
{
	if (m_particle->isDead())
		return;

	PlacementParticle::update();
	
	const auto& bounds = m_scene->getCaveDimensions();
	const auto position = m_placement->GetPos();
	auto velocity = m_particle->getVelocity();

	float X = position.x;
	float Y = position.y;
	float Z = position.z;

	if (Z + m_radius > -bounds.thickness || Z - m_radius < -bounds.depth + bounds.thickness)
	{
		velocity.z(-velocity.z());
		Z = std::clamp(Z, -bounds.depth + bounds.thickness + m_radius, bounds.thickness - m_radius);
	}
	if (Y - m_radius < bounds.thickness || Y + m_radius > bounds.height - bounds.thickness)
	{
		velocity.y(-velocity.y());
		Y = std::clamp(Y, bounds.thickness + m_radius, bounds.height - bounds.thickness - m_radius);
	}
	if (X - m_radius < bounds.thickness || X + m_radius > bounds.width - bounds.thickness)
	{
		velocity.x(-velocity.x());
		X = std::clamp(X, bounds.thickness + m_radius, bounds.width - bounds.thickness - m_radius);
	}

	m_particle->setVelocity(velocity);

	m_particle->setPosition(Todes::Vector3D(X, Y, Z));
}

void ClayPigeon::reset()
{ }

void ClayPigeon::kill()
{
	const auto count = Todes::Random::Size_t(m_payloadBounds.countMin, m_payloadBounds.countMax);

	for (std::size_t i = 0; i < count; ++i)
	{
		// Initialize Placement
		auto piecePlacement = new Vektoria::CPlacement();

		// Translate Placement to position of this firework
		const auto size = Todes::Random::Float(m_payloadBounds.sizeMin, m_payloadBounds.sizeMax);
		piecePlacement->TranslateDelta(m_placement->GetPos());

		// Create Muzzle Force
		Todes::Vector3D muzzleForce = Todes::Random::Vec3D(Todes::Random::Float(m_payloadBounds.velocityMin, m_payloadBounds.velocityMax));

		auto piece = new ClayPiece(piecePlacement, m_scene->getCaveDimensions(), size, 1.0f / (size * 0.5f));
		m_scene->registerClayPiece(piece);

		// Add Muzzle Force
		piece->getParticle()->setVelocity(muzzleForce);
	}

	m_particle->sendDeath();
	m_placement->SwitchOff();
	destroy();
}

void ClayPigeon::revive() const
{ }

void ClayPigeon::destroy()
{
	m_placement->SubPlacement(m_geoPlacement);
	m_geoPlacement->SubGeo(m_geo);
	delete m_geoPlacement;
	PlacementParticle::destroy();
}

const float& ClayPigeon::getRadius() const
{
	return m_radius;
}
