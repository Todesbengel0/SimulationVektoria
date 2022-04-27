#include "Random.h"
#include <cassert>
#include <utility>
#include <ctime>
#include <limits>

namespace Todes
{
	void Random::seed()
	{
		seed((unsigned int)time(nullptr));
	}

	void Random::seed(const unsigned int seed)
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

	int Random::Integer(const int min, const int max)
	{
		assert(min <= max);

		if (min == max)
			return min;

		return rand() % (max - min) + min;
	}

	std::size_t Random::Size_t()
	{
		return (std::size_t)(DoubleNorm() * ULLONG_MAX);
	}

	std::size_t Random::Size_t(std::size_t min, std::size_t max)
	{
		assert(min <= max);

		if (min == max)
			return min;

		return Size_t() % (max - min) + min;
	}

	float Random::Float()
	{
		return FloatNorm() * FLT_MAX;
	}

	float Random::Float(const float min, const float max)
	{
		assert(min <= max);

		if (min == max)
			return min;

		return FloatNorm() * (max - min) + min;
	}

	float Random::FloatNorm()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	double Random::Double()
	{
		return DoubleNorm() * DBL_MAX;
	}

	double Random::Double(const double min, const double max)
	{
		assert(min <= max);

		if (min == max)
			return min;

		return DoubleNorm() * (max - min) + min;
	}

	double Random::DoubleNorm()
	{
		return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	}

	Vector3D Random::Vec3D()
	{
		return Vector3D(Float(), Float(), Float());
	}

	Vector3D Random::Vec3D(const float min, const float max)
	{
		return Vector3D(Float(min, max), Float(min, max), Float(min, max));
	}

	Vector3D Random::Vec3D(const Vector3D& min, const Vector3D& max)
	{
		return Vector3D(Float(min.x(), max.x()), Float(min.y(), max.y()), Float(min.z(), max.z()));
	}

	bool Random::Bool(const float chance)
	{
		return FloatNorm() < chance;
	}

	short Random::Sign(float chance)
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
