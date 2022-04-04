#pragma once
#include "CaveScene.h"
#include "ParticleDan.h"
#include "PhysicInterfaces/ParticlePlacement.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleGravity.h"

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
	ParticleDan* m_particleDan1;
	ParticleDan* m_particleDan2;
	Vektoria::CMaterial* m_mSphere1;
	Vektoria::CMaterial* m_mSphere2;
	Vektoria::CGeo* m_gSphere1;
	Vektoria::CGeo* m_gSphere2;

	r3::Particle* m_particleSphere1;
	r3::Particle* m_particleSphere2;
	ParticlePlacement* m_particlePlacementSphere1;
	ParticlePlacement* m_particlePlacementSphere2;

	r3::ParticleGravity* m_gravity;
	glm::vec3 m_downForce;
};