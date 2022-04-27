#pragma once

namespace Vektoria
{
	class CGeoTail;

	class CTailPlacements
	{
	public:
		CTailPlacements(unsigned int tailCount, float maxAge);

		void PutTail(CHMat localMat);

		bool isDead();

		void update(float timeDelta);

	private:
		const unsigned int m_tailCount;
		unsigned int m_currentTail;
		CGeoTail* m_geo;
		CMaterial* m_material;
		std::vector<std::pair<CPlacement*, float>> m_tailParts;
		float m_maxAge;
		bool m_isDead;
	};
}

