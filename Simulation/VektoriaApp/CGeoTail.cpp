#include "pch.h"
#include "CGeoTail.h"
namespace Vektoria
{
	CGeoTail::CGeoTail(CMaterial& zm)
	{
		m_vertexStart.Init(
			CHVector(0.0f, 0.0f, 0.0f, 1.0f),
			CHVector(0.0f, 0.0f, 1.0f, 0.0f),
			CHVector(0.0f, 1.0f, 0.0f, 0.0f),
			0.0f,
			0.0f
		);
		m_vertexEnd.Init(
			CHVector(0.0f, 1.0f, 0.0f, 1.0f),
			CHVector(0.0f, 0.0f, 1.0f, 0.0f),
			CHVector(0.0f, 1.0f, 0.0f, 0.0f),
			0.0f,
			0.0f
		);
		AddVertex(&m_vertexStart);
		AddVertex(&m_vertexEnd);
		CGeoLineList::Init();
		SetMaterial(&zm);
	}

	CGeoTail::CGeoTail()
	{ }

	void CGeoTail::Init(CMaterial& zm, const CHVector& start /*= CHVector(0.0f, 0.0f, 0.0f, 1.0f) */, const CHVector& end /*= CHVector(0.0f, 1.0f, 0.0f, 1.0f)*/)
	{
		m_vertexStart.Init(
			start,
			CHVector(0.0f, 0.0f, 1.0f, 0.0f),
			CHVector(0.0f, 1.0f, 0.0f, 0.0f),
			0.0f,
			0.0f
		);
		m_vertexEnd.Init(
			end,
			CHVector(0.0f, 0.0f, 1.0f, 0.0f),
			CHVector(0.0f, 1.0f, 0.0f, 0.0f),
			0.0f,
			0.0f
		);
		AddVertex(&m_vertexStart);
		AddVertex(&m_vertexEnd);
		CGeoLineList::Init();
		SetMaterial(&zm);
	}

}
