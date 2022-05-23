#pragma once
#include "SimulationScene.h"

class PlacementParticleWorld;
class PlacementParticle;

class SolarSystem : public SimulationScene
{
public:
	explicit SolarSystem();
	~SolarSystem();

	void update(float timeDelta) override;
	void reset() override;

private:
	PlacementParticleWorld* m_particleWorld;
	Vektoria::CGeoSphere m_planetGeo;
	Vektoria::CMaterial m_planetMaterial;
	Vektoria::CPlacement* m_sunPlacement;
	PlacementParticle* m_sun;
	std::vector<Vektoria::CPlacement*> m_planets;
};

