#include "Particle.h"

namespace Todes
{
	Particle::Particle(const Vector3D& position, const float& damping, const float& inverseMass)
		: m_position(position),
		m_damping(damping),
		m_inverseMass(inverseMass),
		m_initialPosition(position),
		m_isDead(false)
	{ }

	Particle::Particle()
		: m_damping(0.999f), m_inverseMass(0.0f), m_isDead(false)
	{ }

	void Particle::setMass(const float& mass)
	{
		if (mass == 0)
			m_inverseMass = std::numeric_limits<float>::max();
		else
			m_inverseMass = 1.0f / mass;
	}

	void Particle::setInverseMass(const float& inverseMass)
	{
		m_inverseMass = inverseMass;
	}

	void Particle::sendDeath(const bool& isDead /*= true*/)
	{
		m_isDead = isDead;
	}

	void Particle::setVelocity(const Vector3D& velocity)
	{
		m_velocity = velocity;
	}

	void Particle::addVelocity(const Vector3D& velocitySummand)
	{
		m_velocity += velocitySummand;
	}

	void Particle::addCurrentAcceleration(const Vector3D& accelerationSummand)
	{
		m_currentAcceleration += accelerationSummand;
	}

	void Particle::setBaseAcceleration(const Vector3D& acceleration)
	{
		m_baseAcceleration = acceleration;
	}

	void Particle::setPosition(const Vector3D& position)
	{
		m_position = position;
	}

	void Particle::translate(const Vector3D& translationVector)
	{
		m_position += translationVector;
	}

	float Particle::getMass() const
	{
		if (m_inverseMass < FINITE_INVERSE_MASS)
			return std::numeric_limits<float>::max();
		return 1.0f / m_inverseMass;
	}

	const float& Particle::getInverseMass() const
	{
		return m_inverseMass;
	}

	const bool& Particle::isDead() const
	{
		return m_isDead;
	}

	const bool Particle::hasFiniteMass() const
	{
		return m_inverseMass >= FINITE_INVERSE_MASS;
	}

	const Todes::Vector3D& Particle::getVelocity() const
	{
		return m_velocity;
	}

	const Todes::Vector3D& Particle::getBaseAcceleration() const
	{
		return m_baseAcceleration;
	}

	const Todes::Vector3D& Particle::getCurrentAcceleration() const
	{
		return m_currentAcceleration;
	}

	const Vector3D& Particle::getPosition() const
	{
		return m_position;
	}

	void Particle::clearAccumulator()
	{
		m_forceAccumulator = Vector3D();
	}

	void Particle::addForce(const Vector3D& force)
	{
		m_forceAccumulator += force;
	}

	void Particle::integrate(float duration)
	{
		if (m_isDead || m_inverseMass < FINITE_INVERSE_MASS) return;

		m_position += m_velocity * duration;

		m_currentAcceleration = m_forceAccumulator * m_inverseMass;

		m_velocity += m_currentAcceleration * duration;

		m_velocity *= powf(m_damping, duration);

		clearAccumulator();
	}

	void Particle::reset()
	{
		m_velocity = Vector3D();
		m_currentAcceleration = Vector3D();
		m_position = m_initialPosition;
	}
}