#pragma once
#include "SimulationScene.h"

class PlacementParticle;
class PlacementParticleWorld;

class SpaceshipScene : public SimulationScene
{
public:
	explicit SpaceshipScene();
	~SpaceshipScene();

	void update(float timeDelta) override;
	void reset() override;

	PlacementParticle* createPlanet(const Vektoria::CHVector& position, const float& radius);

private:
	PlacementParticleWorld* m_particleWorld;
	Vektoria::CGeoSphere m_planetGeo;
	Vektoria::CMaterial m_planetMaterial;
	const float m_gravityConstant;
};

