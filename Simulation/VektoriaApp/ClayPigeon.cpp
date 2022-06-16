#include "pch.h"
#include "ClayPigeon.h"
#include "Scenes/TrapShooting.h"
#include "Particle.h"
#include "Random.h"
#include "PlacementParticleWorld.h"
#include "TodesConverter.h"
#include "ClayPiece.h"

ClayPigeon::ClayPigeon(Vektoria::CPlacement* placement, Vektoria::CPlacement* payloadPlacement, TrapShooting* scene, Vektoria::CGeo* geo, Vektoria::CMaterial* material)
	: PlacementParticle(placement, geo, material, 0.999f, 1.0f)
	, m_scene(scene)
	, m_payloadPlacement(payloadPlacement)
{ }

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

	if (position.z > 0.0f || position.z < -bounds.depth)
		velocity.z(-velocity.z());
	if (position.y < 0.0f || position.y > bounds.height)
		velocity.y(-velocity.y());
	if (position.x < 0.0f || position.x > bounds.width)
		velocity.x(-velocity.x());

	m_particle->setVelocity(velocity);
}

void ClayPigeon::reset()
{ }

void ClayPigeon::kill()
{
	m_particle->sendDeath();
	m_placement->SwitchOff();

	const auto count = Todes::Random::Size_t(m_payloadBounds.countMin, m_payloadBounds.countMax);

	for (std::size_t i = 0; i < count; ++i)
	{
		// Initialize Placement
		auto piecePlacement = new Vektoria::CPlacement();

		// Translate Placement to position of this firework
		piecePlacement->TranslateDelta(convertVector(m_particle->getPosition()));

		// Create Muzzle Force
		Todes::Vector3D muzzleForce = Todes::Random::Vec3D();

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

void ClayPigeon::revive() const
{

}

void ClayPigeon::destroy()
{

}
