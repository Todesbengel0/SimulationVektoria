#pragma once
#include "PlacementParticle.h"

class TrapShooting;

class ClayPigeon : public PlacementParticle
{
public:
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
	ClayPigeon(Vektoria::CPlacement* placement,
		const float& radius, TrapShooting* scene,
		Vektoria::CGeo* geo, Vektoria::CMaterial* material);

public:
	// Updates the pigeon
	void update(const float& timeDelta) override;
	void update() override;

	// We cannot reset a pigeon
	void reset() override;

	// Kills this pigeon and shoots its payload
	void kill() override;

	// We cannot revive a clay pigeon
	void revive() const override;

	void destroy() override;

	const float& getRadius() const;

protected:
	const float m_radius;
	const PayloadBounds m_payloadBounds;
	Vektoria::CPlacement* m_geoPlacement;
	TrapShooting* m_scene;
};

