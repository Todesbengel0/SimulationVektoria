#pragma once
#include <iostream>
#include <math.h>
#include <string>

class Vector3D
{
public:
	Vector3D();
	Vector3D(const float& value);
	Vector3D(const float& x, const float& y, const float& z);
	~Vector3D();

#pragma region Getter & Setter
public:
	const float& x() const;
	const float& y() const;
	const float& z() const;
	const float& x(const float& new_x);
	const float& y(const float& new_y);
	const float& z(const float& new_z);
#pragma endregion

public:
	float LengthSq() const;
	float Length() const;
	Vector3D Norm() const;
	Vector3D& Normalize();
	Vector3D Cross(const Vector3D& rhs) const;
	Vector3D& CrossEqual(const Vector3D& rhs);
	void Print() const;

private:
	float m_x;
	float m_y;
	float m_z;


#pragma region Overloaded Operations
public:
	friend std::ostream& operator<<(std::ostream& os, const Vector3D& vector)
	{
		os << "( " << vector.m_x << " | " << vector.m_y << " | " << vector.m_z << " )";
		return os;
	}
	Vector3D operator+(const Vector3D& rhs) const;
	Vector3D& operator+=(const Vector3D& rhs);
	Vector3D operator-(const Vector3D& rhs) const;
	Vector3D& operator-=(const Vector3D& rhs);
	friend float operator*(const Vector3D& lhs, const Vector3D& rhs)
	{
		return lhs.m_x * rhs.m_x + lhs.m_y * rhs.m_y + lhs.m_z * rhs.m_z;
	}
	friend Vector3D operator*(const float& lhs, const Vector3D& rhs)
	{
		Vector3D result = rhs;
		result.m_x *= lhs;
		result.m_y *= lhs;
		result.m_z *= lhs;
		return result;
	}
	friend Vector3D& operator*=(const float& lhs, Vector3D& rhs)
	{
		rhs.m_x *= lhs;
		rhs.m_y *= lhs;
		rhs.m_z *= lhs;
		return rhs;
	}
	Vector3D operator*(const float rhs) const;
	Vector3D& operator*=(const float rhs);
	Vector3D operator/(const float rhs) const;
	Vector3D& operator/=(const float rhs);
	friend bool operator==(const Vector3D& lhs, const Vector3D& rhs)
	{
		return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y && lhs.m_z == rhs.m_y;
	}
	friend bool operator!=(const Vector3D& lhs, const Vector3D& rhs)
	{
		return !(lhs == rhs);
	}
	friend bool operator>=(const Vector3D& lhs, const Vector3D& rhs)
	{
		return lhs.m_x >= rhs.m_x && lhs.m_y >= rhs.m_y && lhs.m_z >= rhs.m_y;
	}
	friend bool operator<(const Vector3D& lhs, const Vector3D& rhs)
	{
		return !(lhs >= rhs);
	}
	friend bool operator<=(const Vector3D& lhs, const Vector3D& rhs)
	{
		return lhs.m_x <= rhs.m_x && lhs.m_y <= rhs.m_y && lhs.m_z <= rhs.m_y;
	}
	friend bool operator>(const Vector3D& lhs, const Vector3D& rhs)
	{
		return !(lhs <= rhs);
	}
#pragma endregion
};

