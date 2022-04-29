#pragma once

namespace Vektoria
{
	class CGeoTail;

	class CTailPlacements
	{
	public:
		CTailPlacements(CPlacement* rootPlacement, CMaterial* material, const unsigned int& tailCount, const float& maxAge);

		void PutTail(CHMat localMat);

		void update(float timeDelta);

	private:
		const unsigned int m_tailCount;
		unsigned int m_currentTail;
		static CGeoTail* s_geo;
		CMaterial* m_material;
		CPlacements m_tailPlacements;
		std::vector<float> m_tailAge;
		const float m_maxAge;
		bool m_isDead;
		CPlacement* m_rootPlacement;
	};
}

