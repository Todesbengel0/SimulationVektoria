#pragma once
#include "SimulationScene.h"

struct VektoriaObject {
	Vektoria::CPlacement* placement;
	Vektoria::CGeo* geo;
	Vektoria::CMaterial* material;
};

class CaveScene : public SimulationScene
{
public:
	explicit CaveScene();
	~CaveScene();

	void update(float timeDelta) override;
	void reset() override;

protected:
	Vektoria::CPlacement* m_pCave;

	VektoriaObject m_floor;
	VektoriaObject m_leftWall;
	VektoriaObject m_rightWall;
	VektoriaObject m_backWall;
	VektoriaObject m_frontWall;
	VektoriaObject m_ceiling;
};