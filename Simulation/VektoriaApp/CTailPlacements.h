#pragma once

namespace Vektoria
{
	class CGeoTail;

	class CTailPlacements
	{
	public:
		CTailPlacements(CPlacement* rootPlacement, CGeoTail* tailGeo, const unsigned int& tailCount, const float& maxAge);

		void PutTail(CHMat localMat);

		void update(float timeDelta);

	private:
		const unsigned int m_tailCount;
		unsigned int m_currentTail;
		CGeoTail* m_geo;
		CPlacements m_tailPlacements;
		std::vector<float> m_tailAge;
		const float m_maxAge;
		bool m_isDead;
		CPlacement* m_rootPlacement;
	};
}

