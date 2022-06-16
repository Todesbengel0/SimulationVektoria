#pragma once
#include "CaveScene.h"

class PlacementParticleWorld;
class PlacementParticle;
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
	void checkPigeons();
	void createPigeon();

	void registerClayPiece(ClayPiece* piece);

private:
	PlacementParticleWorld* m_particleWorld;
	std::vector<PlacementParticle*> m_balls;
	std::vector<ClayPigeon*> m_pigeons;
	Vektoria::CGeoSphere* m_geoPigeon;
	Vektoria::CMaterial* m_materialPigeon;
	float m_timeSinceBirth;
	const float m_ballRadius;
	Vektoria::CGeoSphere* m_geoBall;
	Vektoria::CMaterial* m_materialBall;
	Canon m_canon;
};