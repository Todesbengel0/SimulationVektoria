#pragma once
#include "CaveScene.h"

class ClayPigeon;
class ClayPiece;

class TrapShooting : public CaveScene
{
public:
	struct Canon {
		Vektoria::CPlacement* transPlacement;
		Vektoria::CPlacement* rotPlacement;
		Vektoria::CMaterial* material;
		Vektoria::CGeoCylinder* geo;
		float height = 6.0f;
		float movementSpeed = 10.0f;
		float rotationSpeed = 0.4f;
	};

public:
	TrapShooting();

	void update(float timeDelta) override;
	void spawn() override;

	void moveCanon(const float& timeDelta);
	void checkBalls();

	void registerClayPiece(ClayPiece* piece);

private:
	PlacementParticleWorld* m_particleWorld;
	std::vector<PlacementParticle*> m_balls;
	const float m_ballRadius;
	Vektoria::CGeoSphere* m_geoBall;
	Vektoria::CMaterial* m_materialBall;
	Canon m_canon;
};