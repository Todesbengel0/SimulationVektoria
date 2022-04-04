#include "CaveScene.h"
#include "Vektoria/Placement.h"

CaveScene::CaveScene()
{
	m_pCave = new Vektoria::CPlacement();
	AddPlacement(m_pCave);
	m_pCave->TranslateXDelta(-10.0f);
	m_pCave->TranslateYDelta(-10.0f);
	m_pCave->TranslateZDelta(-30.0f);

	m_pFloor = new Vektoria::CPlacement();
	m_pFloor->RotateX(UM_DEG2RAD(-90.0f));
	m_pCave->AddPlacement(m_pFloor);
	auto floorGeo = new Vektoria::CGeoWall();
	m_mFloor = new Vektoria::CMaterial();
	m_mFloor->LoadPreset((char*)"WoodPlanksBankirai");
	floorGeo->Init(20.0f, 20.0f, 0.1f, m_mFloor);
	m_pFloor->AddGeo(floorGeo);
	m_gFloor = floorGeo;

	m_pLeftWall = new Vektoria::CPlacement();
	m_pLeftWall->RotateY(UM_DEG2RAD(90.0f));
	m_pCave->AddPlacement(m_pLeftWall);
	auto leftWallGeo = new Vektoria::CGeoWall();
	m_mLeftWall = new Vektoria::CMaterial();
	m_mLeftWall->LoadPreset((char*)"WallOldAuerbach");
	leftWallGeo->Init(20.0f, 20.0f, 0.1f, m_mLeftWall);
	m_pLeftWall->AddGeo(leftWallGeo);
	m_gLeftWall = leftWallGeo;

	m_pRightWall = new Vektoria::CPlacement();
	m_pRightWall->RotateYDelta(UM_DEG2RAD(90.0f));
	m_pRightWall->TranslateXDelta(20.0f);
	m_pCave->AddPlacement(m_pRightWall);
	auto rightWallGeo = new Vektoria::CGeoWall();
	m_mRightWall = new Vektoria::CMaterial();
	m_mRightWall->LoadPreset((char*)"BricksClinkerColored");
	rightWallGeo->Init(20.0f, 20.0f, 0.1f, m_mRightWall);
	m_pRightWall->AddGeo(rightWallGeo);
	m_gRightWall = rightWallGeo;

	m_pBackWall = new Vektoria::CPlacement();
	m_pBackWall->TranslateZ(-20.0f);
	m_pCave->AddPlacement(m_pBackWall);
	auto backWallGeo = new Vektoria::CGeoWall();
	m_mBackWall = new Vektoria::CMaterial();
	m_mBackWall->LoadPreset((char*)"WallFachwerk");
	backWallGeo->Init(20.0f, 20.0f, 0.1f, m_mBackWall);
	m_pBackWall->AddGeo(backWallGeo);
	m_gBackWall = backWallGeo;
}

CaveScene::~CaveScene()
{

}

void CaveScene::update(float timeDelta)
{
	__super::update(timeDelta);
}

void CaveScene::reset()
{

}
