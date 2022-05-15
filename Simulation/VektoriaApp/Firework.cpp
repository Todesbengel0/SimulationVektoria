#include "pch.h"
#include "Firework.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "Scenes/FireworkScene.h"
#include "Random.h"
#include "PlacementParticleWorld.h"

Firework::Firework(Vektoria::CPlacement* placement, FireworkScene* scene,
	Vektoria::CTailPlacements* tails, Vektoria::CGeo* geo, Vektoria::CMaterial* material,
	const std::size_t& number_of_iterations, const PayloadBounds& bounds)
	: PlacementParticle(placement, 0.999f, 1.0f / bounds.massMax),
	m_scene(scene), m_tailPlacements(tails), m_prevPosition(m_particle->getPosition()),
	m_age(0), m_number_of_iterations(number_of_iterations), m_payloadBounds(bounds)
{
	m_geo = geo;
	m_material = material;
	m_geoPlacement = new Vektoria::CPlacement();
	m_geoPlacement->AddGeo(m_geo);
	m_geoPlacement->Scale(m_payloadBounds.sizeMax);
	m_placement->AddPlacement(m_geoPlacement);
}

void Firework::update(const float& timeDelta)
{
	if (m_particle->isDead())
		return;

	m_age += timeDelta;

	PlacementParticle::update();

	const auto& currPosition = m_particle->getPosition();

	auto vecDif = currPosition - m_prevPosition;
	auto posDif = vecDif.Length();
	auto tailVec = Todes::Vector3D(0.0f, 1.0f, 0.0f);
	auto rotAxis = tailVec.Cross(vecDif.Normalize());
	auto dot = vecDif * tailVec;
	auto rotAngle = dot == 1.0f ? 0.0f :
		std::atan2f(rotAxis.Length(), vecDif * tailVec);

	// Rotate Delta From To Version new ?
	Vektoria::CHMat tailMat;

	tailMat.ScaleDelta(posDif);
	if (dot != 1.0f)
		tailMat.RotateDelta(convertVector(rotAxis), rotAngle);
	tailMat.TranslateDelta(convertVector(m_prevPosition));

	m_tailPlacements->PutTail(tailMat);

	m_prevPosition = currPosition;

	if (m_age > m_payloadBounds.ageMax)
	{
		kill();
		return;
	}
}

void Firework::update() const
{
	PlacementParticle::update();
}

void Firework::reset() const
{ }

void Firework::kill()
{
	m_particle->sendDeath();
	m_placement->SwitchOff();

	if (m_number_of_iterations == 0 || m_payloadBounds.countMax == 0)
	{
		destroy();
		return;
	}

	std::size_t numIterations = m_number_of_iterations - 1;

	// Calculate Bounds that are the same for all payloads
	auto ageMax = Todes::Random::Float(m_payloadBounds.ageMin, (numIterations == 0 ? 2.0f : 1.0f) * m_payloadBounds.ageMax);
	auto sizeMax = Todes::Random::Float(m_payloadBounds.sizeMin, m_payloadBounds.sizeMax);
	auto massMax = Todes::Random::Float(m_payloadBounds.massMin, m_payloadBounds.massMax);
	auto velocityMax = Todes::Random::Float(m_payloadBounds.velocityMin, m_payloadBounds.velocityMax);

	// Create Gravity and Geo for Payload
	Gravity* gravity = new Gravity(Todes::Vector3D(0.0f, -9.807f, 0.0f));

	m_material->RotateHue(UM_DEG2RAD(Todes::Random::Float(0.0f, 360.0f)));

	for (std::size_t i = 0; i < m_payloadBounds.countMax; ++i)
	{
		// Initialize Placement
		auto fireworkPlacement = new Vektoria::CPlacement();

		// Translate Placement to position of this firework
		fireworkPlacement->TranslateDelta(convertVector(m_particle->getPosition()));

		// Create Muzzle Force
		Todes::Vector3D muzzleForce = Todes::Random::Vec3D(velocityMax);

		const Firework::PayloadBounds bounds
		{
			m_payloadBounds.ageMin /* ageMin */
			, ageMax /* ageMax */
			, m_payloadBounds.countMin /* countMin */
			, Todes::Random::Size_t(m_payloadBounds.countMin, m_payloadBounds.countMax) /* countMax */
			, m_payloadBounds.massMin /* massMin */
			, massMax /* massMax */
			, m_payloadBounds.sizeMin /* sizeMin */
			, sizeMax /* sizeMax */
			, m_payloadBounds.velocityMin /* velocityMin */
			, (velocityMax - m_payloadBounds.velocityMin) * 0.1f + m_payloadBounds.velocityMin /* velocityMax */
		};

		auto firework = new Firework(fireworkPlacement, m_scene, m_tailPlacements, m_geo, m_material, numIterations, bounds);
		m_scene->registerFirework(firework);

		// Add Muzzle Force
		firework->getParticle()->setVelocity(muzzleForce);
	}

	destroy();
}

void Firework::revive() const
{ }

void Firework::destroy()
{
// 	m_placement->SubPlacement(m_geoPlacement);
// 	m_geoPlacement->SubAll();
//	delete m_geoPlacement;
	PlacementParticle::destroy();
}
