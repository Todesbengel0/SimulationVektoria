#pragma once
#include "Vector3D.h"

namespace Todes
{

	class Random
	{
	public:
		/// <summary>
		/// Seed the random number generator with the current time.
		/// </summary>
		static void seed();

		/// <summary>
		/// Seed the random number generator with a given seed.
		/// </summary>
		/// <param name="seed">The number used as a seed</param>
		static void seed(const unsigned int& seed);

		/// <summary>
		/// Returns the seed, which the random number generator got initialized
		/// </summary>
		static unsigned int getSeed();

		/// <summary>
		/// Returns random integer value between integer_min and integer_max
		/// </summary>
		static int Integer();

		/// <summary>
		/// Calculates random integer value in a user defined range.
		/// </summary>
		/// <param name="min">Minimal value</param>
		/// <param name="max">Maximal value</param>
		/// <returns>Random integer between min and max</returns>
		static int Integer(const int& min, const int& max);

		/// <summary>
		/// Returns random unsigned long long value between std::size_t_min and std::size_t_max
		/// </summary>
		static std::size_t Size_t();

		/// <summary>
		/// Calculates random unsigned long long value in a user defined range.
		/// </summary>
		/// <param name="min">Minimal value</param>
		/// <param name="max">Maximal value</param>
		/// <returns>Random unsigned long long between min and max</returns>
		static std::size_t Size_t(const std::size_t& min, const std::size_t& max);

		/// <summary>
		/// Returns random float value between float_min and float_max
		/// </summary>
		static float Float();

		/// <summary>
		/// Calculates random float value in a user defined range.
		/// </summary>
		/// <param name="min">Minimal value</param>
		/// <param name="max">Maximal value</param>
		/// <returns>Random float between min and max</returns>
		static float Float(const float& min, const float& max);

		/// <summary>
		/// Returns a random float between 0 and 1
		/// </summary>
		static float FloatNorm();

		/// <summary>
		/// Returns random double value between double_min and double_max
		/// </summary>
		static double Double();

		/// <summary>
		/// Calculates random double value in a user defined range.
		/// </summary>
		/// <param name="min">Minimal value</param>
		/// <param name="max">Maximal value</param>
		/// <returns>Random double between min and max</returns>
		static double Double(const double& min, const double& max);

		/// <summary>
		/// Returns a random float between 0 and 1
		/// </summary>
		static double DoubleNorm();

		/// <summary>
		/// Returns a random Vector 3D
		/// </summary>
		static Vector3D Vec3D();

		/// <summary>
		/// Calculate a random Vector 3D in a user defined range.
		/// </summary>
		/// <param name="min">Minimal value for a vector component</param>
		/// <param name="max">Maximal value for a vector component</param>
		/// <returns>Random Vector 3D</returns>
		static Vector3D Vec3D(const float& min, const float& max);

		/// <summary>
		/// Calculate a random 3D vector in a user defined range.
		/// </summary>
		/// <param name="min">Minimal Value</param>
		/// <param name="max">Maximum Value</param>
		/// <returns>Random Vector 3D</returns>
		static Vector3D Vec3D(const Vector3D& min, const Vector3D& max);

		/// <summary>
		/// Returns a random boolean value.
		/// </summary>
		/// <param name="chance">The probability of the boolean value to be true.</param>
		static bool Bool(const float& chance = 0.5f);

		/// <summary>
		/// Returns a signed value of -1 or 1 at random
		/// </summary>
		/// <param name="chance">Probability for number to be signed.</param>
		static short Sign(const float& chance = 0.5f);

	private:
		explicit Random();
		~Random();

		static unsigned int s_seed;
	};

}