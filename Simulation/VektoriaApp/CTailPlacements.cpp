#include "pch.h"
#include "CTailPlacements.h"
#include "CGeoTail.h"

Vektoria::CTailPlacements::CTailPlacements(CPlacement* rootPlacement, CMaterial* material, const unsigned int& tailCount, const float& maxAge)
	: m_material(material), m_tailCount(tailCount), m_maxAge(maxAge), m_currentTail(0), m_isDead(true),
	m_rootPlacement(rootPlacement)
{
	m_geo = new CGeoTail(m_material);

	for (unsigned int i = 0; i < m_tailCount; ++i)
	{
		auto placement = new Vektoria::CPlacement();
		m_tailParts.push_back(std::pair(placement, -1.0f));
		placement->AddGeo(m_geo);
		rootPlacement->AddPlacement(placement);
		placement->SwitchOff();
	}
}

void Vektoria::CTailPlacements::PutTail(CHMat localMat)
{
	m_isDead = false;

	auto& currentTail = m_tailParts[m_currentTail++];
	m_currentTail %= m_tailCount;

	currentTail.first->SwitchOn();
	currentTail.first->SetMat(localMat);
	currentTail.second = 0.0f;
}

void Vektoria::CTailPlacements::update(float timeDelta)
{
	if (m_isDead)
		return;

	bool dead = true;

	for (auto& pair : m_tailParts)
	{
		if (pair.second < 0.0f)
			continue;

		dead = false;

		if (pair.second <= m_maxAge)
		{
			pair.second += timeDelta;
			continue;
		}

		pair.second = -1.0f;

		pair.first->SwitchOff();
	}

	m_isDead = dead;
}
