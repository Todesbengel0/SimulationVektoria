#pragma once
#include "SimulationScene.h"
#include "ForceDefines.h"

struct VektoriaObject {
	Vektoria::CPlacement* placement;
	Vektoria::CGeo* geo;
	Vektoria::CMaterial* material;
};

struct CaveDimensions {
	const float width;
	const float depth;
	const float height;
	const float thickness;
};

class CaveScene : public SimulationScene
{
public:
	explicit CaveScene(
		const float& downForce = -9.807f,
		const float& translationZ = 10.0f,
		const float& caveWidth = 30.0f,
		const float& caveDepth = 20.0f,
		const float& caveHeight = 20.0f,
		const float& wallThickness = 0.1f);
	~CaveScene();

	void update(float timeDelta) override;
	void reset() override;

	const CaveDimensions& getCaveDimensions();
	Vektoria::CPlacement* getCave() const;

protected:
	Vektoria::CPlacement* m_pCave;
	const CaveDimensions m_caveDimensions;
	Gravity* m_gravity;

protected:
	VektoriaObject m_floor;
	VektoriaObject m_leftWall;
	VektoriaObject m_rightWall;
	VektoriaObject m_backWall;
	VektoriaObject m_frontWall;
	VektoriaObject m_ceiling;
};