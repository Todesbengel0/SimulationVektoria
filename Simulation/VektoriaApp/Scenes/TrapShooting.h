#pragma once
#include "CaveScene.h"
#include "Score.h"

class PlacementParticleWorld;
class PlacementParticle;
class ClayPigeon;
class ClayPiece;

class TrapShooting : public CaveScene
{
public:
	struct Canon {
		Vektoria::CPlacement* transPlacement = new Vektoria::CPlacement();
		Vektoria::CPlacement* rotPlacement = new Vektoria::CPlacement();
		Vektoria::CMaterial* material = new Vektoria::CMaterial();
		Vektoria::CGeoCylinder* geo = new Vektoria::CGeoCylinder();
		float height = 8.0f;
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

	std::vector<ClayPigeon*> m_pigeons;
	Vektoria::CGeoSphere* m_geoPigeon;
	Vektoria::CMaterial* m_materialPigeon;
	float m_timeSinceBirth;

	std::vector<PlacementParticle*> m_balls;
	const float m_ballRadius;
	Vektoria::CGeoSphere* m_geoBall;
	Vektoria::CMaterial* m_materialBall;

	Canon m_canon;

	Score m_score;

private:
	Vektoria::COverlay m_scoreOverlay;
	Vektoria::CMaterial m_scoreMaterial;
	Vektoria::CWriting m_scoreWriting;
	Vektoria::CWritingFont m_scoreWritingFont;
};