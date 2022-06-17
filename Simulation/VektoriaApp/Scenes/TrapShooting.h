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
		Vektoria::CPlacement* transPlacement = nullptr;
		Vektoria::CPlacement* rotPlacement = nullptr;
		Vektoria::CMaterial* material = nullptr;
		Vektoria::CGeoCylinder* geo = nullptr;
		float height = 4.0f;
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
	bool m_spawn;

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

	Vektoria::COverlay m_controlsOverlay;
	Vektoria::CMaterial m_controlsMaterial;
	Vektoria::CWriting m_controlsWriting;
	Vektoria::CWritingFont m_controlsFont;
};