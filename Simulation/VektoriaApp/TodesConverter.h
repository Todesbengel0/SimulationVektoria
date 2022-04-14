#pragma once
#include "../Lib/VektoriaMath/HVector.h"

#include "Vector3D.h"

static Vektoria::CHVector convertVector(const Vector3D& vec)
{
	return Vektoria::CHVector(vec.x(), vec.y(), vec.z());
}

static Vector3D convertVector(const Vektoria::CHVector& vec)
{
	return Vector3D(vec.x, vec.y, vec.z);
}
