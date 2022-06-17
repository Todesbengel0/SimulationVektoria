#include "pch.h"
#include "Mockingbird.h"
#include "Particle.h"
#include "Random.h"
#include "Scenes/TrapShooting.h"
#include "ClayPiece.h"

Mockingbird::Mockingbird(Vektoria::CPlacement* placement, Vektoria::CGeoSphere* geo, Vektoria::CMaterial* material, TrapShooting* scene, const Bounds& bounds, const float& radius)
	: PlacementParticle(placement, geo, material, 0.999f, 1.0f)
	, m_scene(scene)
	, m_bounds(bounds)
	, m_radius(radius)
{
	m_looseAnchor = new Todes::Particle(Todes::Vector3D(), 0.999f, 1.0f);

	m_looseSpring = new Todes::ParticleSpring(m_looseAnchor, 0.4f, m_bounds.looseLength);

	m_anchoredSprings.push_back(new Todes::ParticleAnchoredSpring(Todes::Vector3D(), 0.6f, 0.0f));
	m_anchoredSprings.push_back(new Todes::ParticleAnchoredSpring(Todes::Vector3D(), 0.6f, 0.0f));

	replace();

	m_placement->SwitchOff();
}

void Mockingbird::update()
{
	if (m_particle->isDead()) return;

	PlacementParticle::update();

	const auto position = m_placement->GetPos();
	auto velocity = m_particle->getVelocity();

	float X = position.x;
	float Y = position.y;
	float Z = position.z;

	if (Z - m_radius < m_bounds.zMin || Z + m_radius > m_bounds.zMax)
	{
		velocity.z(-velocity.z());
		Z = std::clamp(Z, m_bounds.zMin + m_radius, m_bounds.zMax - m_radius);
	}
	if (Y - m_radius < 0.0f || Y + m_radius > m_bounds.anchorHeight)
	{
		velocity.y(-velocity.y());
		Y = std::clamp(Y, m_radius, m_bounds.anchorHeight - m_radius);
	}
	if (X - m_radius < m_bounds.xMin || X + m_radius > m_bounds.xMax)
	{
		velocity.x(-velocity.x());
		X = std::clamp(X, m_bounds.xMin + m_radius, m_bounds.xMax - m_radius);
	}

	m_particle->setVelocity(velocity);

	m_particle->setPosition(Todes::Vector3D(X, Y, Z));

	auto scale = Z / (m_bounds.zMin - m_bounds.zMax);
	m_material->Scale(scale, scale, scale);
}

void Mockingbird::update(const float& timeDelta)
{
	if (!m_alive)
	{
		m_timeSinceDeath += timeDelta;
		
		if (m_timeSinceDeath > 30.0f)
		{
			m_timeSinceDeath = 0.0f;
			m_alive = true;
			m_placement->SwitchOn();

			update();
		}

		return;
	}

	update();
}

void Mockingbird::reset()
{ }

void Mockingbird::kill()
{
	m_alive = false;

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

	m_placement->SwitchOff();
}

void Mockingbird::revive() const
{ }

const std::vector<Todes::ParticleAnchoredSpring*>& Mockingbird::getAnchoredForces()
{
	return m_anchoredSprings;
}

Todes::ParticleSpring* Mockingbird::getLooseForce()
{
	return m_looseSpring;
}

Todes::Particle* Mockingbird::getLooseAnchor()
{
	return m_looseAnchor;
}

const bool& Mockingbird::isAlive()
{
	return m_alive;
}

const float& Mockingbird::getRadius()
{
	return m_radius;
}

void Mockingbird::replace()
{
	const auto loosePosition = Todes::Random::Vec3D
		( Todes::Vector3D(m_bounds.xMin, m_bounds.looseHeightMin, m_bounds.zMin)
		, Todes::Vector3D(m_bounds.xMax, m_bounds.looseHeightMax, m_bounds.zMax));
	m_looseAnchor->reset();
	m_looseAnchor->setPosition(loosePosition);

	m_particle->reset();
	m_particle->setPosition(Todes::Vector3D(loosePosition.x(), loosePosition.y() - m_bounds.looseLength, loosePosition.z()));

	for (auto anchoredSpring : m_anchoredSprings)
	{
		anchoredSpring->setOtherEnd(Todes::Random::Vec3D
			( Todes::Vector3D(m_bounds.xMin, m_bounds.anchorHeight, m_bounds.zMin)
			, Todes::Vector3D(m_bounds.xMax, m_bounds.anchorHeight, m_bounds.zMax)));

		anchoredSpring->setRestLength((anchoredSpring->getOtherEnd() - loosePosition).Length()
			* Todes::Random::Float(0.9f, 0.98f));
	}


}
