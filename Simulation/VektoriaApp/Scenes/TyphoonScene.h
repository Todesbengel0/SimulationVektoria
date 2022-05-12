#pragma once
#include "CaveScene.h"

class PlacementParticle;
class PlacementParticleWorld;

class TyphoonScene : public CaveScene
{
public:
	explicit TyphoonScene();
	~TyphoonScene();

	void update(float timeDelta) override;
	void reset() override;

protected:
	PlacementParticleWorld* m_particleWorld;
};
