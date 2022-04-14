#pragma once
#include "CaveScene.h"
#include "Particle.h"
#include "PlacementParticle.h"

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
	std::vector<PlacementParticle*> m_ppBalls;
	Vector3D m_downForce;
	Canon m_canon;
};

