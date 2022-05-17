#pragma once

namespace Vektoria
{
	class CGeoTail : public CGeoLineList
	{
	public:
		CGeoTail();
		CGeoTail(CMaterial& zm);

		void Init(CMaterial& zm
			, const CHVector& start = CHVector(0.0f, 0.0f, 0.0f, 1.0f)
			, const CHVector& end = CHVector(0.0f, 1.0f, 0.0f, 1.0f));

	private:
		CVertex m_vertexStart;
		CVertex m_vertexEnd;
	};

}