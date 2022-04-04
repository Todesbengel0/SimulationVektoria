#pragma once
#include "CaveScene.h"
#include "ParticleDan.h"
#include <iostream>
#include <vector>

struct PlacementParticle {
	Vektoria::CPlacement* placement;
	Vektoria::CGeo* geo;
	ParticleDan* particle;
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
	Vektoria::CPlacement* m_pCanon;
	Vektoria::CMaterial* m_mCanon;
	Vektoria::CGeo* m_gCanon;
	float m_canonHeight;
};

