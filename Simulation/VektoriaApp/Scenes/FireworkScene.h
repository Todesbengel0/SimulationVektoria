#pragma once
#include "Scenes/CaveScene.h"
#include "ForceDefines.h"

class PlacementParticle;
class PlacementParticleWorld;
namespace Vektoria { class CGeoTail;  }

class FireworkScene : public CaveScene
{

public:
	explicit FireworkScene();
	~FireworkScene();

	void update(float timeDelta) override;
	void spawn() override;

	PlacementParticleWorld* getWorld() const;

	unsigned int getCurrentTail();

public:
	Vektoria::CPlacements m_tails;

protected:
	PlacementParticleWorld* m_particleWorld;
	Vektoria::CMaterial* m_fireworkMaterial;
	Vektoria::CGeoTail* m_tail;
	unsigned int m_currentTail;
	Gravity* m_gravity;
};

