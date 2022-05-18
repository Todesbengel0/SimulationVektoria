#include "pch.h"
#include "SimulationScene.h"
#include "Game.h"

SimulationScene::SimulationScene()
	: m_bWASDCam(true)
{
	m_camera.Init(QUARTERPI);

	m_cameraPlacement.AddCamera(&m_camera);
	m_cameraPlacement.SetTranslationSensitivity(10.0f);
	m_cameraPlacement.SetRotationSensitivity(1.0f);
	m_cameraPlacement.TranslateZ(8.0f);
	this->AddPlacement(&m_cameraPlacement);

	this->SetLightAmbient(Vektoria::CColor(0.4f, 0.4f, 0.4f));
}

void SimulationScene::regMaterial(Vektoria::CMaterial* pzm)
{
	CGame::GetInstance().getRoot().AddMaterial(pzm);
	m_materials.emplace(pzm);
}

SimulationScene::~SimulationScene()
{
	// unload additionally-registered Materials from the root node
	for (auto& pzm : m_materials)
		CGame::GetInstance().getRoot().SubMaterial(pzm);
}

void SimulationScene::update(float timeDelta)
{
	m_physicsEngine.tick(timeDelta);
}

void SimulationScene::reset()
{
}

void SimulationScene::spawn()
{
}

void SimulationScene::activate()
{

}

Vektoria::CCamera& SimulationScene::getCamera()
{
	return m_camera;
}

Vektoria::CPlacement& SimulationScene::getCameraPlacement()
{
	return m_cameraPlacement;
}

void SimulationScene::setWASDCam(bool wasdCam)
{
	m_bWASDCam = wasdCam;
}

bool SimulationScene::getWASDCam() const
{
	return m_bWASDCam;
}
