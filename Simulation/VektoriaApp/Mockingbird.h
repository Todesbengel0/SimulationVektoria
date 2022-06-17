#pragma once
#include "PlacementParticle.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleSpring.h"

class TrapShooting;

class Mockingbird : public PlacementParticle
{
public:
	struct Bounds {
		float xMin;
		float xMax;
		float zMin;
		float zMax;
		float anchorHeight;
		float looseHeightMin;
		float looseHeightMax;
		float looseLength;
	};
	struct PayloadBounds
	{
		const std::size_t countMin = 20;
		const std::size_t countMax = 50;
		const float sizeMin = 0.01f;
		const float sizeMax = 0.05f;
		const float velocityMin = 2.0f;
		const float velocityMax = 5.0f;
	};

public:
	Mockingbird(Vektoria::CPlacement* placement, Vektoria::CGeoSphere* geo, Vektoria::CMaterial* material
		, TrapShooting* scene, const Bounds& bounds, const float& radius);

	void update(const float& timeDelta) override;
	void update() override;

	// We cannot reset a pigeon
	void reset() override;

	// Kills this pigeon and shoots its payload
	void kill() override;

	// We cannot revive a clay pigeon
	void revive() const override;

public:
	const std::vector<Todes::ParticleAnchoredSpring*>& getAnchoredForces();
	Todes::ParticleSpring* getLooseForce();
	Todes::Particle* getLooseAnchor();
	const bool& isAlive();
	const float& getRadius();

protected:
	void replace();

private:
	TrapShooting* m_scene;

	Todes::Particle* m_looseAnchor;

	Todes::ParticleSpring* m_looseSpring;
	std::vector<Todes::ParticleAnchoredSpring*> m_anchoredSprings;

	const Bounds m_bounds;
	const PayloadBounds m_payloadBounds;
	const float m_radius;

	float m_timeSinceDeath = 0.0f;
	bool m_alive = false;
};

