#pragma once
#include "Scenes/CaveScene.h"
#include "ForceDefines.h"

class PlacementParticle;
class PlacementParticleWorld;

class FireworkScene : public CaveScene
{

public:
	explicit FireworkScene();
	~FireworkScene();

	void update(float timeDelta) override;
	void spawn() override;

	PlacementParticleWorld* getWorld() const;

protected:
	PlacementParticleWorld* m_particleWorld;
	Vektoria::CMaterial* m_fireworkMaterial;
	Gravity* m_gravity;
};

