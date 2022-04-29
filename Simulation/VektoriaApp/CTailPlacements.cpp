#include "pch.h"
#include "CTailPlacements.h"
#include "CGeoTail.h"

Vektoria::CTailPlacements::CTailPlacements(CPlacement* rootPlacement, CGeoTail* tailGeo, const unsigned int& tailCount, const float& maxAge)
	: m_geo(tailGeo), m_tailCount(tailCount), m_maxAge(maxAge), m_currentTail(0), m_isDead(true),
	m_rootPlacement(rootPlacement)
{

	for (unsigned int i = 0; i < m_tailCount; ++i)
	{
		auto placement = new Vektoria::CPlacement();
		m_tailPlacements.Add(placement);
		m_tailAge.push_back(-1.0f);
		placement->AddGeo(m_geo);
		rootPlacement->AddPlacement(placement);
		placement->SwitchOff();
	}
}

void Vektoria::CTailPlacements::PutTail(CHMat localMat)
{
	m_isDead = false;

	m_tailAge[m_currentTail] = 0.0f;

	auto& currentTail = m_tailPlacements.m_applacement[m_currentTail++];
	m_currentTail %= m_tailCount;

	currentTail->SwitchOn();
	currentTail->SetMat(localMat);
}

void Vektoria::CTailPlacements::update(float timeDelta)
{
	if (m_isDead)
		return;

	bool dead = true;

	for (std::size_t i = 0; i < m_tailCount; ++i)
	{
		auto& age = m_tailAge[i];

		if (age < 0.0f)
			continue;

		dead = false;

		if (age <= m_maxAge)
		{
			age += timeDelta;
			continue;
		}

		age = -1.0f;

		m_tailPlacements.m_applacement[i]->SwitchOff();
	}

	m_isDead = dead;
}
