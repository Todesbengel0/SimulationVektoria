#include "Particle.h"

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

const float& Particle::getMass() const
{
	if (m_inverseMass == 0)
		return std::numeric_limits<float>::max();
	return 1.0f / m_inverseMass;
}

const bool& Particle::isDead() const
{
	return m_isDead;
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
	if (m_isDead || m_inverseMass <= 0) return;

	m_position += m_velocity * duration;

	auto resultingAcceleration = m_acceleration;
	resultingAcceleration += m_forceAccumulator * m_inverseMass;

	m_velocity += resultingAcceleration * duration;

	m_velocity *= powf(m_damping, duration);

	clearAccumulator();
}

void Particle::reset()
{
	m_velocity = Vector3D();
	m_acceleration = Vector3D();
	m_position = m_initialPosition;
}
