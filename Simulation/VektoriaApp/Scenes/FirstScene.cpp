#include "pch.h"
#include "FirstScene.h"
#include "Vektoria/Placement.h"
#include "Vektoria/GeoSphere.h"
#include "PhysicInterfaces/ParticlePlacementWorld.h"

FirstScene::FirstScene()
{
	m_pSphere1 = new Vektoria::CPlacement();
	m_pSphere1->SwitchOff();
	m_pCave->AddPlacement(m_pSphere1);
	m_pSphere1->TranslateX(10.0f);
	m_pSphere1->TranslateYDelta(15.0f);
	m_pSphere1->TranslateZDelta(-5.0f);

	m_pSphere2 = new Vektoria::CPlacement();
	m_pSphere2->SwitchOff();
	m_pCave->AddPlacement(m_pSphere2);
	m_pSphere2->TranslateX(20.0f);
	m_pSphere2->TranslateYDelta(15.0f);
	m_pSphere2->TranslateZDelta(-5.0f);

	m_mSphere1 = new Vektoria::CMaterial();
	m_mSphere1->LoadPreset((char*)"PhongGrey");
	regMaterial(m_mSphere1);
	m_mSphere2 = new Vektoria::CMaterial();
	m_mSphere2->LoadPreset((char*)"Sun");
	regMaterial(m_mSphere2);

	auto sphereGeo1 = new Vektoria::CGeoSphere();
	sphereGeo1->Init(0.5f, m_mSphere1);
	auto sphereGeo2 = new Vektoria::CGeoSphere();
	sphereGeo2->Init(0.5f, m_mSphere2);

	m_pSphere1->AddGeo(sphereGeo1);
	m_gSphere1 = sphereGeo1;
	m_pSphere2->AddGeo(sphereGeo2);
	m_gSphere2 = sphereGeo2;

	m_particle1 = new Todes::Particle(Todes::Vector3D(m_pSphere1->GetPos().x, m_pSphere1->GetPos().y, m_pSphere1->GetPos().z), 0.999f, 1.0f);
	m_particle2 = new Todes::Particle(Todes::Vector3D(m_pSphere2->GetPos().x, m_pSphere2->GetPos().y, m_pSphere2->GetPos().z), 0.999f, 0.1f);


	m_downForce = Todes::Vector3D(0.0f, -9.807f, 0.0f);
}

FirstScene::~FirstScene()
{
}

void FirstScene::update(float timeDelta)
{
	__super::update(timeDelta);

	if (!m_pSphere1->IsOn())
		return;
	auto force1 = m_particle1->getMass() * m_downForce;
	auto force2 = m_particle2->getMass() * m_downForce;

	m_particle1->addForce(force1);
	m_particle2->addForce(force2);
	m_particle1->integrate(timeDelta);
	m_particle2->integrate(timeDelta);

	auto position1 = m_particle1->getPosition();
	auto position2 = m_particle2->getPosition();

	auto vekvec1 = Vektoria::CHVector(position1.x(), position1.y(), position1.z());
	auto vekvec2 = Vektoria::CHVector(position2.x(), position2.y(), position2.z());

	m_pSphere1->Translate(vekvec1);
	m_pSphere2->Translate(vekvec2);

}

void FirstScene::reset()
{
// 	m_particleSphere1->reset();
// 	m_particleSphere2->reset();
	m_particle1->reset();
	m_particle2->reset();
}

void FirstScene::spawn()
{
	m_pSphere1->SwitchOn();
	m_pSphere2->SwitchOn();
	//reset();
}
