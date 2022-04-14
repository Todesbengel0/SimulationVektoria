#pragma once
#include "CaveScene.h"
#include "Particle.h"

class FirstScene : public CaveScene
{
public:
	explicit FirstScene();
	~FirstScene();

	void update(float timeDelta) override;
	void reset() override;
	void spawn() override;

private:
	Vektoria::CPlacement* m_pSphere1;
	Vektoria::CPlacement* m_pSphere2;
	Particle* m_particle1;
	Particle* m_particle2;
	Vektoria::CMaterial* m_mSphere1;
	Vektoria::CMaterial* m_mSphere2;
	Vektoria::CGeo* m_gSphere1;
	Vektoria::CGeo* m_gSphere2;

	Vector3D m_downForce;
};