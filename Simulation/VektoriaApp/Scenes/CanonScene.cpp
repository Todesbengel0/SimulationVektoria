#include "Vektoria/Placement.h"
#include "Vektoria/GeoSphere.h"
#include "Vektoria/GeoCylinder.h"
#include "CanonScene.h"

CanonScene::CanonScene()
{
	m_downForce = glm::vec3(0.0f, -9.807f, 0.0f);

	m_pCanon = new Vektoria::CPlacement();
	m_pCave->AddPlacement(m_pCanon);
	m_pCanon->TranslateX(13.0f);
	m_pCanon->TranslateYDelta(-7.0f);
	m_pCanon->TranslateZDelta(-10.0f);
	Vektoria::CHVector canonDirection = m_pCanon->GetDirection();
	m_pCanon->RotateZDelta(UM_DEG2RAD(25.0f));
	m_pCanon->RotateXDelta(UM_DEG2RAD(10.0f));
	canonDirection = m_pCanon->GetDirection();
	
	auto canonGeo = new Vektoria::CGeoCylinder();
	m_mCanon = new Vektoria::CMaterial();
	m_mCanon->LoadPreset((char*)"MetalRustyFlaking");
	canonGeo->Init(2.5f, 1.5f, m_canonHeight = 5.0f, m_mCanon);
	m_pCanon->AddGeo(canonGeo);
	m_gCanon = canonGeo;
}

CanonScene::~CanonScene()
{
	for (auto& pp : m_ppBalls)
	{
		if (pp->particle)
			delete pp->particle;
		if (pp->placement)
			delete pp->placement;
		delete pp;
	}
}

void CanonScene::update(float timeDelta)
{
	__super::update(timeDelta);
	for (auto pp : m_ppBalls)
	{
		if (!pp->particle || !pp->placement)
			continue;
		if (pp->particle->isDead())
			continue;
		auto force = pp->particle->getMass() * m_downForce;
		//pp->particle->addForce(force);
		pp->particle->integrate(timeDelta);
		auto position = pp->particle->getPosition();
		auto vekvec = Vektoria::CHVector(position.x, position.y, position.z);
		pp->placement->Translate(vekvec);
	}
}

void CanonScene::reset()
{
	for (auto pp : m_ppBalls)
	{
		if (!pp->particle || !pp->placement)
			continue;
		if (pp->particle->isDead())
			continue;
		pp->particle->sendDeath();
		pp->placement->SwitchOff();
	}
}

void CanonScene::spawn()
{
	m_ppBalls.push_back(new PlacementParticle);
	auto pp = m_ppBalls.back();
	pp->placement = new Vektoria::CPlacement();
	m_pCanon->AddPlacement(pp->placement);
	auto gBall = new Vektoria::CGeoSphere();
	gBall->Init(1.0f, nullptr);
	pp->placement->AddGeo(gBall);
	pp->geo = gBall;
	auto canonDirection = m_pCanon->GetDirection();
//  	Vektoria::CHVector muzzlePosition = Vektoria::CHVector(canonDirection.GetX(), canonDirection.GetY(), -m_pCanon->GetDirection().GetZ()) * m_canonHeight;
	pp->placement->TranslateY(m_canonHeight * 0.5f);
	pp->particle = new ParticleDan(glm::vec3(pp->placement->GetPos().x, pp->placement->GetPos().y, pp->placement->GetPos().z), 0.999f, 1.0f);
	float muzzleVelocity = m_canonHeight * 250.0f;
	glm::vec3 shootDirection = glm::vec3(canonDirection.GetX(), m_canonHeight * (1.0f - canonDirection.GetY()), -canonDirection.GetZ());
	glm::vec3 muzzleForce = shootDirection * (muzzleVelocity / shootDirection.length());
	pp->particle->addForce(muzzleForce);
	// TODO: Kugel spawnt an Mündung
}
