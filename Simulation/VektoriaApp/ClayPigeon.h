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
		const float sizeMin = 0.05f;
		const float sizeMax = 0.2f;
		const float velocityMin = 2.0f;
		const float velocityMax = 5.0f;
	};

public:
	ClayPigeon(Vektoria::CPlacement* placement, Vektoria::CPlacement* payloadPlacement, TrapShooting* scene,
		Vektoria::CGeo* geo, Vektoria::CMaterial* material);

public:
	// Updates the firework
	void update(const float& timeDelta) override;
	void update() override;

	// We cannot reset a firework
	void reset() override;

	// Kills this firework and shoots its payload
	void kill() override;

	// We cannot revive a firework
	void revive() const override;

	// Destroys the firework
	void destroy() override;

protected:
	const PayloadBounds m_payloadBounds;
	Vektoria::CPlacement* m_payloadPlacement;
	TrapShooting* m_scene;
};

