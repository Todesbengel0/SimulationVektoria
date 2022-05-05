#pragma once
#include "CaveScene.h"

class PlacementParticle;
class PlacementParticleWorld;

class SpringScene : public CaveScene
{
public:
	explicit SpringScene();
	~SpringScene();

	void update(float timeDelta) override;
	void move(PlacementParticle* actor, const float& timeDelta);
	void reset() override;
	void spawn() override;

protected:
	PlacementParticleWorld* m_particleWorld;
	PlacementParticle* m_player;
};

