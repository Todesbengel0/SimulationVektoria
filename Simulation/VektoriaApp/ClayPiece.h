#pragma once
#include "PlacementParticle.h"
#include "Scenes/CaveScene.h"

class ClayPiece : public PlacementParticle
{
public:
	ClayPiece(Vektoria::CPlacement* placement, const CaveDimensions& bounds, const float& radius, const float& inverseMass);

	void update() override;

	// Kills the clay piece
	void kill() override;

	// We cannot reset a clay piece
	void reset() override;

	// We cannot revive a clay piece
	void revive() const override;

	void setGeo(Vektoria::CGeo* geo) override;

private:
	Vektoria::CPlacement* m_geoPlacement;
	const float m_radius;
	const CaveDimensions m_bounds;
};

