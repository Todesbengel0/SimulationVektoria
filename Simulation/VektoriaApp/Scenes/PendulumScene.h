#pragma once
#include "CaveScene.h"

class PlacementParticleWorld;
namespace Todes { class ParticleSpring; }

class PendulumScene : public CaveScene
{
public:
	explicit PendulumScene();
	~PendulumScene();

	void update(float timeDelta) override;
	void reset() override;
	void spawn() override;

protected:
	PlacementParticleWorld* m_particleWorld;
	Todes::ParticleSpring* m_linkulum1Spring;
	Todes::ParticleSpring* m_linkulum2Spring;
};

