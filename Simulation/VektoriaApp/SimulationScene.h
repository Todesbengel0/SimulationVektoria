#pragma once

#include "PhysicInterfaces/PhysicsEngineWrapper.h"

class SimulationScene : public Vektoria::CScene
{
public:
	virtual ~SimulationScene();

	/**
	 * Update this scene
	 * It is called update() instead of tick(), since there is
	 * already a Tick() method defined in Vektora::Scene
	 */
	virtual void update(float timeDelta);

	/** Reset the scene to its initial state. */
	virtual void reset();

	/** Spawn placements in scene */
	virtual void spawn();

	/** Calls this method at the start */
	virtual void activate();

	Vektoria::CCamera& getCamera();
	Vektoria::CPlacement& getCameraPlacement();

	void setWASDCam(bool wasdCam);
	bool getWASDCam() const;

protected:
	explicit SimulationScene();

	/**
	 * Materialien die nicht im ersten Tick() referenziert werden,
	 * müssen der Engine extra bekanntgemacht werden,
	 * damit diese geladen werden!
	 * Hierzu diese Funktion zusätzlich zu Vektoria::CMaterial::Init() aufrufen!
	 */
	void regMaterial(Vektoria::CMaterial* pzm);

	// necessary Vektoria scene components
	Vektoria::CCamera m_zc;
	Vektoria::CPlacement m_zpCamera;

	PhysicsEngineWrapper m_physicsEngine;

private:
	// WASD camera movement by game
	bool m_bWASDCam;

	// additionally-registered Materials by the scene
	std::set<Vektoria::CMaterial*> m_materials;
};
