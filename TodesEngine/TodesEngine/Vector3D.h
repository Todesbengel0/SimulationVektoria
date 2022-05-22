#pragma once
#include <iostream>
#include <math.h>
#include <string>

namespace Todes
{
	/// <summary>
	/// Class for working with three dimensional mathematical vectors
	/// </summary>
	class Vector3D
	{
#pragma region Constructor & Destructor
	public:
		/// <summary>
		/// Creates a Null-Vector
		/// </summary>
		Vector3D();

		/// <summary>
		/// Creates a 3D Vector with equal values.
		/// </summary>
		/// <param name="value">Value that the parameters shall have.</param>
		Vector3D(const float& value);

		/// <summary>
		/// Creates a 3D Vector with given values.
		/// </summary>
		/// <param name="x">Value for x parameter.</param>
		/// <param name="y">Value for y parameter.</param>
		/// <param name="z">Value for z parameter.</param>
		Vector3D(const float& x, const float& y, const float& z);

		/// <summary>
		/// Creates a normalized 3D Vector that points along the given axis.
		/// </summary>
		/// <param name="xDirection">TRUE: Vector points along x axis.</param>
		/// <param name="yDirection">TRUE: Vector points along y axis.</param>
		/// <param name="zDirection">TRUE: Vector points along z axis.</param>
		Vector3D(const bool& xDirection, const bool& yDirection, const bool& zDirection);
		~Vector3D();
#pragma endregion

#pragma region Getter & Setter
	public:
		/// <summary>
		/// Returns the x-coordinate of the vector
		/// </summary>
		const float& x() const;

		/// <summary>
		/// Returns the y-coordinate of the vector
		/// </summary>
		const float& y() const;

		/// <summary>
		/// Returns the z-coordinate of the vector
		/// </summary>
		const float& z() const;

		/// <summary>
		/// Sets the x-coordinate of the vector
		/// </summary>
		/// <param name="new_x">new x-coordinate</param>
		void x(const float& new_x);

		/// <summary>
		/// Sets the y-coordinate of the vector
		/// </summary>
		/// <param name="new_y">new y-coordinate</param>
		void y(const float& new_y);

		/// <summary>
		/// Sets the z-coordinate of the vector
		/// </summary>
		/// <param name="new_z">new z-coordinate</param>
		void z(const float& new_z);
#pragma endregion

	public:
		/// <summary>
		/// Returns the squared Length of the Vector
		/// </summary>
		float LengthSq() const;

		/// <summary>
		/// Returns the Length of the Vector
		/// </summary>
		float Length() const;

		/// <summary>
		/// Returns a Vector representing the normalized version of this vector
		/// </summary>
		/// <returns>A new Vector 3D</returns>
		Vector3D Norm() const;

		/// <summary>
		/// Normalizes this vector
		/// </summary>
		/// <returns>This Vector after being normalized</returns>
		Vector3D& Normalize();

		/// <summary>
		/// Calculates the Cross Product between this Vector and another
		/// </summary>
		/// <param name="rhs">Other Vector to calculate Cross Product with</param>
		/// <returns>A new Vector 3D</returns>
		Vector3D Cross(const Vector3D& rhs) const;

		/// <summary>
		/// Calculates the Cross Product between this Vector and another
		/// </summary>
		/// <param name="rhs">Other Vector to calculate Cross Product with</param>
		/// <returns>This Vector after being changed to the cross product</returns>
		Vector3D& CrossEqual(const Vector3D& rhs);

		/// <summary>
		/// Rotates this Vector around the x-axis
		/// </summary>
		/// <param name="radiant">Rotation angle in rad</param>
		/// <returns>This Vector after being rotated</returns>
		Vector3D& RotateX(const float& radiant);

		/// <summary>
		/// Rotates this Vector around the y-axis
		/// </summary>
		/// <param name="radiant">Rotation angle in rad</param>
		/// <returns>This Vector after being rotated</returns>
		Vector3D& RotateY(const float& radiant);

		/// <summary>
		/// Rotates this Vector around the z-axis
		/// </summary>
		/// <param name="radiant">Rotation angle in rad</param>
		/// <returns>This Vector after being rotated</returns>
		Vector3D& RotateZ(const float& radiant);

		/// <summary>
		/// Rotates this Vector around a given rotation axis
		/// </summary>
		/// <param name="rotationAngle">Rotation angle in rad</param>
		/// <param name="rotationAxis">Axis to rotate this vector around</param>
		/// <returns>This Vector after being rotated</returns>
		Vector3D& Rotate(const float& rotationAngle, const Vector3D& rotationAxis);

		/// <summary>
		/// Rotates the Vector to point towards a position
		/// </summary>
		/// <param name="position">Position to point towards</param>
		Vector3D& RotateTo(const Vector3D& position);

		/// <summary>
		/// Checks if the Vector is a null vector.
		/// </summary>
		/// <returns>TRUE: Vector is null vector. FALSE: Vector is not null vector.</returns>
		bool isNull() const;

	private:
		float m_x;
		float m_y;
		float m_z;


#pragma region Overloaded Operations
	public:
		/// <summary>
		/// Prints this vector
		/// </summary>
		friend std::ostream& operator<<(std::ostream& os, const Vector3D& vector)
		{
			os << "( " << vector.m_x << " | " << vector.m_y << " | " << vector.m_z << " )";
			return os;
		}
		Vector3D operator+() const;
		Vector3D operator+(const Vector3D& rhs) const;
		Vector3D& operator+=(const Vector3D& rhs);
		Vector3D operator-() const;
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
}
