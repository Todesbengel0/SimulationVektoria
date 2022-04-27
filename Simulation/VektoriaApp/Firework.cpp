#include "pch.h"
#include "Firework.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "Scenes/FireworkScene.h"
#include "Random.h"
#include "PlacementParticleWorld.h"

Firework::Firework(FireworkScene& scene, Vektoria::CPlacement* placement, Vektoria::CGeoSphere* geo, Vektoria::CMaterial* material, const std::size_t& number_of_iterations, const PayloadBounds& bounds)
	: PlacementParticle(placement, geo, material, 0.999f, 1.0f / bounds.massMax),
	m_scene(scene), m_prevPosition(m_particle->getPosition()),
	m_age(0), m_number_of_iterations(number_of_iterations), m_payloadBounds(bounds)
{
	m_placement->AddGeo(m_geo);
}

void Firework::update(const float& timeDelta)
{
	if (m_particle->isDead())
		return;

	m_age += timeDelta;

	if (m_age > m_payloadBounds.ageMax)
	{
		kill();
		return;
	}

	PlacementParticle::update();

	auto tail = m_scene.m_tails.m_applacement[m_scene.getCurrentTail()];
	tail->SwitchOn();

	auto currPosition = m_particle->getPosition();

	auto posDif = (m_prevPosition - currPosition).Length();

	// Rotate Delta From To Version new ? 
	Vektoria::CHMat rotMat;
	rotMat.Scale(posDif);
	rotMat.RotateDelta(convertVector(currPosition), convertVector(m_prevPosition));
	rotMat.TranslateDelta(convertVector(m_prevPosition));

	tail->SetMat(rotMat);

	m_prevPosition = currPosition;
}

void Firework::update() const
{
	PlacementParticle::update();
}

void Firework::reset() const
{ }

void Firework::kill() const
{
	m_particle->sendDeath();
	m_placement->SwitchOff();

	if (m_number_of_iterations == 0 || m_payloadBounds.countMax == 0)
		return;

	std::size_t numIterations = m_number_of_iterations - 1;

	// Calculate Bounds that are the same for all payloads
	auto ageMax = Todes::Random::Float(m_payloadBounds.ageMin, (numIterations == 0 ? 2.0f : 1.0f) * m_payloadBounds.ageMax);
	auto sizeMax = Todes::Random::Float(m_payloadBounds.sizeMin, m_payloadBounds.sizeMax);
	auto massMax = Todes::Random::Float(m_payloadBounds.massMin, m_payloadBounds.massMax);
	auto velocityMax = Todes::Random::Float(m_payloadBounds.velocityMin, m_payloadBounds.velocityMax);

	// Create Gravity and Geo for Payload
	Gravity* gravity = new Gravity(Todes::Vector3D(0.0f, -9.807f, 0.0f));
	auto geo = new Vektoria::CGeoSphere();
	geo->Init(sizeMax, m_material);

	m_material->RotateHue(UM_DEG2RAD(Todes::Random::Float(0.0f, 360.0f)));

	for (std::size_t i = 0; i < m_payloadBounds.countMax; ++i)
	{
		// Initialize Placement
		auto fireworkPlacement = new Vektoria::CPlacement();
		m_scene.getCave()->AddPlacement(fireworkPlacement);

		// Translate Placement to position of this firework
		fireworkPlacement->TranslateDelta(convertVector(m_particle->getPosition()));

		// Create Muzzle Force
		Todes::Vector3D muzzleForce = Todes::Random::Vec3D(
										Todes::Vector3D(-1.0f, -1.0f, -1.0f).Norm(),
										Todes::Vector3D(1.0f, 1.0f, 1.0f).Norm())
									* velocityMax;

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
			, (velocityMax - m_payloadBounds.velocityMin) * 0.2f + m_payloadBounds.velocityMin /* velocityMax */
		};

		auto firework = new Firework(m_scene, fireworkPlacement, geo, m_material, numIterations, bounds);
		m_scene.getWorld()->addPlacementParticle(firework, { gravity });

		// Add Muzzle Force
		firework->getParticle()->addForce(muzzleForce);
		firework->getParticle()->integrate(1.0f);
		firework->update();
	}
}

void Firework::revive() const
{ }
