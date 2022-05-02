#include "pch.h"
#include "Firework.h"
#include "TodesConverter.h"
#include "Particle.h"
#include "Scenes/FireworkScene.h"
#include "Random.h"
#include "PlacementParticleWorld.h"
#include "CGeoTail.h"

Firework::Firework(Vektoria::CPlacement* placement, FireworkScene* scene,
	Vektoria::CMaterial* material,
	const std::size_t& number_of_iterations, const PayloadBounds& bounds)
	: PlacementParticle(placement, 0.999f, 1.0f / bounds.massMax),
	m_scene(scene), m_prevPosition(m_particle->getPosition()),
	m_age(0), m_number_of_iterations(number_of_iterations), m_payloadBounds(bounds)
{
	auto geo = new Vektoria::CGeoSphere();
	m_material = new Vektoria::CMaterial(*material);
	geo->Init(1.0f, m_material);
	m_geo = geo;
	m_geoPlacement = new Vektoria::CPlacement();
	m_geoPlacement->AddGeo(m_geo);
	m_geoPlacement->Scale(m_payloadBounds.sizeMax);
	m_placement->AddPlacement(m_geoPlacement);

	m_tailPlacements = new Vektoria::CTailPlacements(new Vektoria::CGeoTail(m_material), 10, 1.25f);

	scene->registerFirework(this, m_tailPlacements);
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

	const auto& currPosition = m_particle->getPosition();

	auto vecDif = currPosition - m_prevPosition;
	auto posDif = vecDif.Length();
	auto tailVec = Todes::Vector3D(0.0f, 1.0f, 0.0f);
	//auto rotAxis = vecDif.Normalize().Cross(tailVec);
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

	m_material->RotateHue(UM_DEG2RAD(Todes::Random::Float(0.0f, 360.0f)));

	for (std::size_t i = 0; i < m_payloadBounds.countMax; ++i)
	{
		// Initialize Placement
		auto fireworkPlacement = new Vektoria::CPlacement();

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
			, (velocityMax - m_payloadBounds.velocityMin) * 0.1f + m_payloadBounds.velocityMin /* velocityMax */
		};

		auto firework = new Firework(fireworkPlacement, m_scene, m_material, numIterations, bounds);

		// Add Muzzle Force
		firework->getParticle()->addForce(muzzleForce);
		firework->getParticle()->integrate(1.0f);
		firework->update();
	}

	
	destroy();
}

void Firework::revive() const
{ }

void Firework::destroy()
{
 	m_placement->SubPlacement(m_geoPlacement);
 	//delete m_geoPlacement;
	//delete m_geo;
	//delete m_material;
	m_tailPlacements->destroy();
	PlacementParticle::destroy();
}
