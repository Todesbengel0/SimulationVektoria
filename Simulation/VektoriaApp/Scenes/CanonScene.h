#pragma once
#include "CaveScene.h"
#include "ForceDefines.h"

class PlacementParticle;
class PlacementParticleWorld;

struct Canon {
	Vektoria::CPlacement* placement;
	Vektoria::CMaterial* material;
	Vektoria::CGeo* geo;
	float zRotation;
	float xRotation;
	float height;
};

class CanonScene : public CaveScene
{
public:
	explicit CanonScene();
	~CanonScene();

	void update(float timeDelta) override;
	void reset() override;
	void spawn() override;

protected:
	PlacementParticleWorld* m_particleWorld;
	Vektoria::CGeoSphere* m_geoBall;
	Vektoria::CMaterial* m_materialBall;
	Canon m_canon;
};

