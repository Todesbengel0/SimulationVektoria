#pragma once

class SimulationScene;
class CGame
{
// singleton
private:
	CGame();
public:
	CGame(const CGame&) = delete;
	CGame(CGame&&) = delete;
	~CGame();
	CGame& operator=(const CGame&) = delete;
	CGame& operator=(CGame&&) = delete;
	static CGame& GetInstance();

public:
	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), Vektoria::CSplash* psplash);
	void Tick(float fTime, float fTimeDelta);
	void Fini();

	void WindowReSize(int iNewWidth, int iNewHeight);

	// Holt das minimale Zeitdelta zur eventuellen Frame-Rate-Beschränkung:
	float GetTimeDeltaMin();

	// Holt die Versionsnummer:
	float GetVersion();

	/** Get the root node */
	Vektoria::CRoot& getRoot();
	/** Get the keyboard */
	Vektoria::CDeviceKeyboard& getKeyboard();
	/** Get the mouse */
	Vektoria::CDeviceMouse& getMouse();
	/** Get the viewport*/
	Vektoria::CViewport& getViewport();

private:
	void initScenes();
	void addScene(SimulationScene* scene);
	void changeScene(int sceneIdx);
	void changeScene(SimulationScene* scene);

	/** Handle user input for scene changing. */
	void handleUserInput();

	/** Change the active scene to the next one. */
	void nextScene();
	/** Change the active scene to the previous one. */
	void prevScene();

private:
    // Hier ist Platz für Deine Vektoriaobjekte:
	Vektoria::CRoot m_zr;
	Vektoria::CFrame m_zf;
	Vektoria::CViewport m_zv;
	Vektoria::CLightParallel m_zl;
	Vektoria::CBackground m_zb;

	/* Input */
	Vektoria::CDeviceKeyboard m_keyboard;
	Vektoria::CDeviceMouse m_mouse;

	/* Scenes */
	SimulationScene* m_activeScene;
	std::vector<SimulationScene*> m_scenes;
	std::size_t m_activeSceneIndex;
};


