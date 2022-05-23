#include "pch.h"
#include "Game.h"

#include "Scenes/Scenes.h"

// singleton
CGame& CGame::GetInstance()
{
	static CGame instance;
	return instance;
}

CGame::CGame()
	: m_activeScene(nullptr)
	, m_activeSceneIndex(0)
{
}

CGame::~CGame()
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), Vektoria::CSplash* psplash)
{
	//---------------------------------
	// Initialisiere die Knotenobjekte:
	//---------------------------------

	// Zuallererst muss die Root mit dem Splash-Screen initialisiert werden, 
	// damit die Engine freigeschaltet wird:
	m_zr.Init(psplash);

	// Verwende DirectX12 und nicht DirectX11.
	// Falls kein Bild erscheint oder der Rechner abstürzen sollte, hast du einen Rechner, der nicht DirectX12-kompatibel ist. 
	// Dann kannst du das DirectX11 SDK installieren (siehe Manual, erster Foliensatz) und hier eApiRender_DirectX11_Shadermodel50_Standard eintragen:
	m_zf.SetApiRender(Vektoria::eApiRender_DirectX11_Shadermodel50_Standard);
	//m_zf.SetApiRender(Vektoria::eApiRender_DirectX12);

	// Begrenze die Bildwiederholrate auf max. 100 Hz, damit empfindliche Rechner nicht überhitzen:
	m_zr.SetFrameRateMax(100.0f);

	// Initialisiere den Frame (Fensterrenderbereich):
	m_zf.Init(hwnd, procOS);

	// Initialisiere ein weißes Parallellicht, welches von rechts oben vorne strahlt:
	m_zl.Init(Vektoria::CHVector(1.0f, 1.0f, 1.0f), Vektoria::CColor(1.0f, 1.0f, 1.0f));
	
	//----------------------------
	// Vernetze die Knotenobjekte:
	//----------------------------

	// Hänge den Frame an die Root:
	m_zr.AddFrame(&m_zf);

	// Hänge den Viewport an den Frame:
	m_zf.AddViewport(&m_zv);
 
// 	m_zv.SetBloomOn();
// 	m_zv.SetBloomStrengthNear(6.0f);
// 	m_zv.SetBloomStrengthFar(3.0f);
// 	m_zv.SetBloomWidth(1.5f);

	// Init devices
	m_zf.AddDeviceKeyboard(&m_keyboard);
	m_zf.AddDeviceMouse(&m_mouse);

	// Init scenes
	initScenes();
	changeScene(0); // initial scene
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Root must tick first! (initializes game on first tick)
	m_zr.Tick(fTimeDelta);

	if (m_activeScene)
	{
		m_activeScene->update(fTimeDelta);
		if (m_activeScene->getWASDCam()) m_keyboard.PlaceWASD(m_activeScene->getCameraPlacement(), fTimeDelta);
	}
	handleUserInput();

	// Prevent very high framerates, that can cause hardware damage
	// Comment out, if you have low FPS / reliable hardware
	// Can be removed, once Vektoria::CRoot::SetFrameRateMax() starts working properly
//	Sleep(1u);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}

Vektoria::CRoot& CGame::getRoot()
{
	return m_zr;
}

Vektoria::CDeviceKeyboard& CGame::getKeyboard()
{
	return m_keyboard;
}

Vektoria::CDeviceMouse& CGame::getMouse()
{
	return m_mouse;
}

void CGame::initScenes()
{
	// ADD NEW SCENES HERE
// 	addScene(new FirstScene);
// 	addScene(new CanonScene);
//	addScene(new FireworkScene);
// 	addScene(new SpringScene);
	addScene(new TyphoonScene);
	addScene(new PendulumScene);
	addScene(new SpaceshipScene);
	addScene(new SolarSystem);
}

void CGame::addScene(SimulationScene* scene)
{
	scene->AddLightParallel(&m_zl);
	m_scenes.push_back(scene);
}

void CGame::changeScene(int sceneIdx)
{
	assert(sceneIdx >= 0 && sceneIdx < m_scenes.size());
	changeScene(m_scenes[sceneIdx]);
}

void CGame::changeScene(SimulationScene* scene)
{
	if (m_activeScene)
	{
		m_zr.SubScene(m_activeScene);
	}

	m_activeScene = scene;

	if (scene)
	{
		m_zv.InitFull(&scene->getCamera());
		scene->activate();
		
		m_zr.AddScene(scene);
	}
}

void CGame::handleUserInput()
{
	if (m_keyboard.KeyDown(DIK_1))
	{
		prevScene();
	}
	else if (m_keyboard.KeyDown(DIK_2))
	{
		nextScene();
	}

	if (m_keyboard.KeyDown(DIK_T))
	{
		m_activeScene->reset();
	}

	if (m_keyboard.KeyDown(DIK_B) || m_mouse.ButtonPressedLeft())
	{
		m_activeScene->spawn();
	}
}

void CGame::nextScene()
{
	const auto sceneCount = m_scenes.size();
	if (sceneCount <= 1) return;

	m_activeSceneIndex = (m_activeSceneIndex + 1) % sceneCount;
	changeScene(m_scenes[m_activeSceneIndex]);
}

void CGame::prevScene()
{
	const auto sceneCount = m_scenes.size();
	if (sceneCount <= 1) return;

	if (m_activeSceneIndex-- == 0) m_activeSceneIndex = sceneCount - 1;
	changeScene(m_scenes[m_activeSceneIndex]);
}
