#pragma once
#include "PlacementParticle.h"

class FireworkScene;

class Firework : public PlacementParticle
{
public:
	struct PayloadBounds
	{
		const float ageMin;
		const float ageMax;
		const std::size_t countMin;
		const std::size_t countMax;
		const float massMin;
		const float massMax;
		const float sizeMin;
		const float sizeMax;
		const float velocityMin;
		const float velocityMax;
	};

public:
	Firework(FireworkScene& scene, Vektoria::CPlacement* placement,
		Vektoria::CGeo* geo, Vektoria::CMaterial* material,
		const std::size_t& number_of_iterations, const PayloadBounds& bounds);

public:
	// Updates the firework
	void update(const float& timeDelta) override;
	void update() const override;

	// We cannot reset a firework
	void reset() const override;
	
	// Kills this firework and shoots its payload
	void kill() const override;

	// We cannot revive a firework
	void revive() const override;

protected:
	float m_age;
	const std::size_t m_number_of_iterations;
	const PayloadBounds m_payloadBounds;
	Vektoria::CPlacement* m_geoPlacement;
	Todes::Vector3D m_prevPosition;
	FireworkScene& m_scene;
};

