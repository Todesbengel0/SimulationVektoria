#pragma once
#include "CaveScene.h"
#include "Score.h"

class PlacementParticleWorld;
class PlacementParticle;
class ClayPigeon;
class ClayPiece;
class Mockingbird;

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
		bool inverted = false;
	};
	struct PigeonArray {
		const unsigned int count = 5;
		ClayPigeon** pigeons = new ClayPigeon*[count];
		Vektoria::CGeoSphere** geos = new Vektoria::CGeoSphere*[count];
		Vektoria::CMaterial** materials = new Vektoria::CMaterial*[count];
		float spawnTimeDelta = 0.0f;
		unsigned int currentCount = 0;
		bool spawn = true;
	};

public:
	TrapShooting();
	~TrapShooting();

	void update(float timeDelta) override;
	void spawn() override;

	void moveCanon(const float& timeDelta);
	void checkBalls();
	void checkPigeons();
	void createPigeon();

	void registerClayPiece(ClayPiece* piece);

private:
	PlacementParticleWorld* m_particleWorld;

	PigeonArray m_pigeons;
	Vektoria::CGeoSphere* m_clayPieceGeo;
	Vektoria::CMaterial* m_clayPieceMaterial;

	Mockingbird* m_mockingbird;

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