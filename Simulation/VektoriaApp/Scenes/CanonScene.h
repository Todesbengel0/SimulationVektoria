#pragma once
#include "CaveScene.h"
#include "ParticleDan.h"
#include <iostream>
#include <vector>

struct PlacementParticle {
	Vektoria::CPlacement* placement;
	Vektoria::CGeo* geo;
	Vektoria::CMaterial* material;
	ParticleDan* particle;
};

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
	glm::vec3 m_downForce;
	Canon m_canon;
};

