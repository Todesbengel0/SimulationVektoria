#include "Vector3D.h"

namespace Todes
{
#pragma region Constructor & Destructor
	Vector3D::Vector3D()
		: m_x(0.0f), m_y(0.0f), m_z(0.0f)
	{ }

	Vector3D::Vector3D(const float& value)
		: m_x(value), m_y(value), m_z(value)
	{

	}

	Vector3D::Vector3D(const float& x, const float& y, const float& z)
		: m_x(x), m_y(y), m_z(z)
	{ }

	Vector3D::Vector3D(const bool& xDirection, const bool& yDirection, const bool& zDirection)
	{
		if (!xDirection && !yDirection && !zDirection)
		{
			m_x = 0.0f;
			m_y = 0.0f;
			m_z = 0.0f;
			return;
		}

		if (xDirection && !yDirection && !zDirection)
		{
			m_x = 1.0f;
			m_y = 0.0f;
			m_z = 0.0f;
			return;
		}

		if (!xDirection && yDirection && !zDirection)
		{
			m_x = 0.0f;
			m_y = 1.0f;
			m_z = 0.0f;
			return;
		}

		if (!xDirection && !yDirection && zDirection)
		{
			m_x = 0.0f;
			m_y = 0.0f;
			m_z = 1.0f;
			return;
		}

		m_x = xDirection ? 1.0f : 0.0f;
		m_y = yDirection ? 1.0f : 0.0f;
		m_z = zDirection ? 1.0f : 0.0f;
		Normalize();
	}

	Vector3D::~Vector3D()
	{
	}
#pragma endregion

#pragma region Getter & Setter
	const float& Vector3D::x() const
	{
		return m_x;
	}

	const float& Vector3D::x(const float& new_x)
	{
		return m_x = new_x;
	}

	const float& Vector3D::y() const
	{
		return m_y;
	}

	const float& Vector3D::y(const float& new_y)
	{
		return m_y = new_y;
	}

	const float& Vector3D::z() const
	{
		return m_z;
	}

	const float& Vector3D::z(const float& new_z)
	{
		return m_z = new_z;
	}
#pragma endregion

#pragma region Public Functions
	float Vector3D::LengthSq() const
	{
		return powf(m_x, 2) + powf(m_y, 2) + powf(m_z, 2);
	}

	float Vector3D::Length() const
	{
		return sqrtf(powf(m_x, 2) + powf(m_y, 2) + powf(m_z, 2));
	}

	Vector3D Vector3D::Norm() const
	{
		return *this / Length();
	}

	Vector3D& Vector3D::Normalize()
	{
		return *this /= Length();
	}

	Vector3D Vector3D::Cross(const Vector3D& rhs) const
	{
		Vector3D result;
		result.m_x = m_y * rhs.m_z - m_z * rhs.m_y;
		result.m_y = m_z * rhs.m_x - m_x * rhs.m_z;
		result.m_z = m_x * rhs.m_y - m_y * rhs.m_x;
		return result;
	}

	Vector3D& Vector3D::CrossEqual(const Vector3D& rhs)
	{
		float x, y;
		x = m_y * rhs.m_z - m_z * rhs.m_y;
		y = m_z * rhs.m_x - m_x * rhs.m_z;
		m_z = m_x * rhs.m_y - m_y * rhs.m_x;
		m_x = x;
		m_y = y;
		return *this;
	}

	Vector3D& Vector3D::RotateX(const float& radiant)
	{
		const auto cos = std::cosf(radiant);
		const auto sin = std::sinf(radiant);
		m_y = cos * m_y - sin * m_z;
		m_z = sin * m_y + cos * m_z;

		return *this;
	}

	Vector3D& Vector3D::RotateY(const float& radiant)
	{
		const auto cos = std::cosf(radiant);
		const auto sin = std::sinf(radiant);
		m_x = cos * m_x + sin * m_z;
		m_z = - sin * m_x + cos * m_z;

		return *this;
	}

	Vector3D& Vector3D::RotateZ(const float& radiant)
	{
		const auto cos = std::cosf(radiant);
		const auto sin = std::sinf(radiant);
		m_x = cos * m_x - sin * m_y;
		m_y = sin * m_y + cos * m_x;

		return *this;
	}

	void Vector3D::Print() const
	{
		std::cout << "( " << m_x << " | " << m_y << " | " << m_z << " )";
	}

	bool Vector3D::isZero() const
	{
		return m_x == 0.0f && m_y == 0.0f && m_z == 0.0f;
	}

	Vector3D Vector3D::operator+(const Vector3D& rhs) const
	{
		Vector3D result = *this;
		result.m_x += rhs.m_x;
		result.m_y += rhs.m_y;
		result.m_z += rhs.m_z;
		return result;
	}

	Vector3D& Vector3D::operator+=(const Vector3D& rhs)
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;
		return *this;
	}

	Vector3D Vector3D::operator+() const
	{
		Vector3D result = *this;
		return result;
	}

	Vector3D Vector3D::operator-(const Vector3D& rhs) const
	{
		Vector3D result = *this;
		result.m_x -= rhs.m_x;
		result.m_y -= rhs.m_y;
		result.m_z -= rhs.m_z;
		return result;
	}

	Vector3D& Vector3D::operator-=(const Vector3D& rhs)
	{
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;
		return *this;
	}

	Vector3D Vector3D::operator-() const
	{
		Vector3D result;
		result.m_x = -m_x;
		result.m_y = -m_y;
		result.m_z = -m_z;
		return result;
	}

	Vector3D Vector3D::operator*(const float rhs) const
	{
		Vector3D result = *this;
		result.m_x *= rhs;
		result.m_y *= rhs;
		result.m_z *= rhs;
		return result;
	}

	Vector3D& Vector3D::operator*=(const float rhs)
	{
		m_x *= rhs;
		m_y *= rhs;
		m_z *= rhs;
		return *this;
	}

	Vector3D Vector3D::operator/(const float rhs) const
	{
		Vector3D result = *this;
		result.m_x /= rhs;
		result.m_y /= rhs;
		result.m_z /= rhs;
		return result;
	}

	Vector3D& Vector3D::operator/=(const float rhs)
	{
		m_x /= rhs;
		m_y /= rhs;
		m_z /= rhs;
		return *this;
	}
}