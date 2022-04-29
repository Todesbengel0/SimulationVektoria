#pragma once
#include "Scenes/CaveScene.h"
#include "ForceDefines.h"
#include "CTailPlacements.h"

class PlacementParticle;
class PlacementParticleWorld;
namespace Vektoria { class CGeoTail; }

class FireworkScene : public CaveScene
{

public:
	explicit FireworkScene();
	~FireworkScene();

	void update(float timeDelta) override;
	void spawn() override;

	PlacementParticleWorld* getWorld() const;

public:
	Vektoria::CTailPlacements* m_tail;

protected:
	PlacementParticleWorld* m_particleWorld;
	Vektoria::CMaterial* m_fireworkMaterial;
	Vektoria::CGeoSphere* m_fireworkGeo;
	Vektoria::CGeoTail* m_tailGeo;
	Gravity* m_gravity;
};

