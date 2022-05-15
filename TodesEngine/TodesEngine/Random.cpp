#include "Random.h"
#include <cassert>
#include <utility>
#include <ctime>
#include <limits>
constexpr float PI = 3.1415927f;
constexpr float TWOPI = 6.283185f;

namespace Todes
{
	void Random::seed()
	{
		seed((unsigned int)time(nullptr));
	}

	void Random::seed(const unsigned int& seed)
	{
		s_seed = seed;
		srand(seed);
	}

	unsigned int Random::getSeed()
	{
		return s_seed;
	}

	int Random::Integer()
	{
		return rand();
	}

	int Random::Integer(const int& min, const int& max)
	{
		assert(min <= max);

		auto dif = max - min;
		if (dif == 0)
			return min;

		return rand() % dif + min;
	}

	std::size_t Random::Size_t()
	{
		return (std::size_t)(DoubleNorm() * ULLONG_MAX);
	}

	std::size_t Random::Size_t(const std::size_t& min, const std::size_t& max)
	{
		assert(min <= max);

		auto dif = max - min;
		if (dif == 0)
			return min;

		return Size_t() % dif + min;
	}

	float Random::Float()
	{
		return FloatNorm() * FLT_MAX;
	}

	float Random::Float(const float& min, const float& max)
	{
		assert(min <= max);

		auto dif = max - min;
		if (dif == 0)
			return min;

		return FloatNorm() * dif + min;
	}

	float Random::FloatNorm()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	double Random::Double()
	{
		return DoubleNorm() * DBL_MAX;
	}

	double Random::Double(const double& min, const double& max)
	{
		assert(min <= max);

		auto dif = max - min;
		if (dif == 0)
			return min;

		return DoubleNorm() * dif + min;
	}

	double Random::DoubleNorm()
	{
		return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	}

	Vector3D Random::Vec3D()
	{
		return Vector3D(Float(), Float(), Float());
	}

	Vector3D Random::Vec3D(const float& min, const float& max)
	{
		return Vector3D(Float(min, max), Float(min, max), Float(min, max));
	}

	Vector3D Random::Vec3D(const Vector3D& min, const Vector3D& max)
	{
		return Vector3D(Float(min.x(), max.x()), Float(min.y(), max.y()), Float(min.z(), max.z()));
	}

	Vector3D Random::Vec3D(const float& length)
	{
		Vector3D surfacePoint;

		// Calculate a uniformly distributed z
		surfacePoint.z(-1.0f + 2.0f * FloatNorm());

		// Calculate a uniformly distributed longitude
		const auto longitude = 2.0f * PI * FloatNorm();

		// Horizontal Radius (= r * sin(colatitude), with r = 1)
		const auto rh = std::sqrtf(1.0f - surfacePoint.z() * surfacePoint.z());

		// Calculate x and y coordinates
		surfacePoint.x(rh * std::cosf(longitude));
		surfacePoint.y(rh * std::sinf(longitude));

		// Now we need to scale the surface point by the given length
		return surfacePoint * length;
	}

	Vector3D Random::Vec3D(const float& length, const Vector3D& axis)
	{
		// Calculate a random angle between 0 and TWOPI
		const auto angle = FloatNorm() * TWOPI;

		// Get a Vector that is orthogonal to the axis
		Vector3D orthogonal;
		if (axis.x() != 0.0f)
		{
			orthogonal.y(axis.x());
			orthogonal.x(-axis.y());
		}
		else if (axis.y() != 0.0f)
			orthogonal.x(axis.y());
		else
			orthogonal.x(axis.z());

		// Normalize the Vector
		orthogonal.Normalize();

		// Rotate it by the angle around the axis
		orthogonal.Rotate(angle, axis);

		// Return it scaled by the given length
		return orthogonal * length;
	}

	bool Random::Bool(const float& chance)
	{
		if (chance == 0.0f) return false;
		if (chance == 1.0f) return true;

		return FloatNorm() < chance;
	}

	short Random::Sign(const float& chance)
	{
		if (Bool(chance))
			return -1;

		return 1;
	}

	Random::Random()
		= default;

	Random::~Random()
		= default;

	unsigned int Random::s_seed = 0;
}
