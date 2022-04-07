#include "pch.h"
#include "CaveScene.h"
#include "Vektoria/Placement.h"
#define CaveWidth 30.0f
#define CaveDepth 20.0f
#define CaveHeight 20.0f
#define WallThickness 0.1f

CaveScene::CaveScene()
{
	m_pCave = new Vektoria::CPlacement();
	AddPlacement(m_pCave);
	m_pCave->TranslateXDelta(-CaveWidth * 0.5f);
	m_pCave->TranslateYDelta(-CaveHeight * 0.5f);
	m_pCave->TranslateZDelta(-CaveDepth - 10.0f);

	m_floor.placement = new Vektoria::CPlacement();
	m_floor.placement->RotateX(UM_DEG2RAD(-90.0f));
	m_pCave->AddPlacement(m_floor.placement);
	auto floorGeo = new Vektoria::CGeoWall();
	m_floor.material = new Vektoria::CMaterial();
	m_floor.material->LoadPreset((char*)"WoodPlanksBankirai");
	floorGeo->Init(CaveWidth, CaveDepth, WallThickness, m_floor.material, false, false, true, false, true, false);
	m_floor.placement->AddGeo(floorGeo);
	m_floor.geo = floorGeo;

	m_leftWall.placement = new Vektoria::CPlacement();
	m_leftWall.placement->RotateY(UM_DEG2RAD(90.0f));
	m_pCave->AddPlacement(m_leftWall.placement);
	auto leftWallGeo = new Vektoria::CGeoWall();
	m_leftWall.material = new Vektoria::CMaterial();
	m_leftWall.material->LoadPreset((char*)"WallOldAuerbach");
	leftWallGeo->Init(CaveDepth, CaveHeight, WallThickness, m_leftWall.material, true, false, false, false, true, false);
	m_leftWall.placement->AddGeo(leftWallGeo);
	m_leftWall.geo = leftWallGeo;

	m_rightWall.placement = new Vektoria::CPlacement();
	m_rightWall.placement->RotateYDelta(UM_DEG2RAD(90.0f));
	m_rightWall.placement->TranslateXDelta(CaveWidth);
	m_pCave->AddPlacement(m_rightWall.placement);
	auto rightWallGeo = new Vektoria::CGeoWall();
	m_rightWall.material = new Vektoria::CMaterial();
	m_rightWall.material->LoadPreset((char*)"BricksClinkerColored");
	rightWallGeo->Init(CaveDepth, CaveHeight, WallThickness, m_rightWall.material, true, false, false, false, false, true);
	m_rightWall.placement->AddGeo(rightWallGeo);
	m_rightWall.geo = rightWallGeo;

	m_backWall.placement = new Vektoria::CPlacement();
	m_backWall.placement->TranslateZ(-CaveDepth);
	m_pCave->AddPlacement(m_backWall.placement);
	auto backWallGeo = new Vektoria::CGeoWall();
	m_backWall.material = new Vektoria::CMaterial();
	m_backWall.material->LoadPreset((char*)"WallFachwerk");
	backWallGeo->Init(CaveWidth, CaveHeight, WallThickness, m_backWall.material, false, false, false, false, true, false);
	m_backWall.placement->AddGeo(backWallGeo);
	m_backWall.geo = backWallGeo;

	m_frontWall.placement = new Vektoria::CPlacement();
	m_pCave->AddPlacement(m_frontWall.placement);
	auto frontWallGeo = new Vektoria::CGeoWall();
	m_frontWall.material = new Vektoria::CMaterial();
	m_frontWall.material->LoadPreset((char*)"Glass");
	m_frontWall.material->SetTransparencyOn();
	m_frontWall.material->SetTransparency(0.9f);
	frontWallGeo->Init(CaveWidth, CaveHeight, WallThickness, m_frontWall.material, false, false, false, false, true, false);
	m_frontWall.placement->AddGeo(frontWallGeo);
	m_frontWall.geo = frontWallGeo;

	m_ceiling.placement = new Vektoria::CPlacement();
	m_ceiling.placement->RotateX(UM_DEG2RAD(-90.0f));
	m_ceiling.placement->TranslateYDelta(CaveHeight);
	m_pCave->AddPlacement(m_ceiling.placement);
	auto ceilingGeo = new Vektoria::CGeoWall();
	m_ceiling.material = new Vektoria::CMaterial();
	m_ceiling.material->LoadPreset((char*)"TilesMarbleWhite");

	ceilingGeo->Init(CaveWidth, CaveDepth, WallThickness, m_ceiling.material, false, false, true, false, false, true);
	m_ceiling.placement->AddGeo(ceilingGeo);
	m_ceiling.geo = ceilingGeo;
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
