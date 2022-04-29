#pragma once

namespace Vektoria
{
	class CGeoTail : public CGeoLineList
	{
	public:
		CGeoTail(CMaterial& zm);
		CGeoTail();

		CVertex m_vertexStart;
		CVertex m_vertexEnd;

	};

}