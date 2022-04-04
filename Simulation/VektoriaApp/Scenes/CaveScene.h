#pragma once
#include "SimulationScene.h"


class CaveScene : public SimulationScene
{
public:
	explicit CaveScene();
	~CaveScene();

	void update(float timeDelta) override;
	void reset() override;

protected:
	Vektoria::CPlacement* m_pCave;

	Vektoria::CPlacement* m_pFloor;
	Vektoria::CGeo* m_gFloor;
	Vektoria::CMaterial* m_mFloor;
	Vektoria::CPlacement* m_pLeftWall;
	Vektoria::CGeo* m_gLeftWall;
	Vektoria::CMaterial* m_mLeftWall;
	Vektoria::CPlacement* m_pRightWall;
	Vektoria::CGeo* m_gRightWall;
	Vektoria::CMaterial* m_mRightWall;
	Vektoria::CPlacement* m_pBackWall;
	Vektoria::CGeo* m_gBackWall;
	Vektoria::CMaterial* m_mBackWall;
};