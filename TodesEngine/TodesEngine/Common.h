#pragma once
#define nearlyEqual(a, b)	(float(a - b) < 0.01f && float(a - b) > -0.01f)
#define nearZero(a)			(a < 0.01f && a > -0.01f)
constexpr auto PI = 3.1415927f;
constexpr auto TWOPI = 6.283185f;
constexpr auto SIXPI = 18.849556f;
constexpr auto FOURTHIRDPI = 4.1887902f;
constexpr auto THIRDPI = 1.0471976f;