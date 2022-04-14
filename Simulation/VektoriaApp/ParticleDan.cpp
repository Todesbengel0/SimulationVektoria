#include "pch.h"
#include "ParticleDan.h"

ParticleDan::ParticleDan(glm::vec3 position, float damping, float inverseMass)
{
	m_position = position;
	m_initialPosition = position;
	m_damping = damping;
	m_inverseMass = inverseMass;
	m_forceAccumulator = glm::vec3(0.0f, 0.0f, 0.0f);
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	m_isDead = false;
}

void ParticleDan::setMass(float mass)
{
	if (mass == 0)
		m_inverseMass = std::numeric_limits<float>::max();
	else
		m_inverseMass = 1.0f / mass;

}

void ParticleDan::setInverseMass(float inverseMass)
{
	m_inverseMass = inverseMass;
}

void ParticleDan::sendDeath(bool isDead)
{
	m_isDead = isDead;
}

float ParticleDan::getMass() const
{
	if (m_inverseMass == 0)
		return std::numeric_limits<float>::max();
	return 1.0f / m_inverseMass;
}

bool ParticleDan::isDead() const
{
	return m_isDead;
}

glm::vec3 ParticleDan::getPosition() const
{
	return m_position;
}

void ParticleDan::clearAccumulator()
{
	m_forceAccumulator = glm::vec3(0.0f, 0.0f, 0.0f);
}

void ParticleDan::addForce(const glm::vec3& force)
{
	m_forceAccumulator += force;
}

void ParticleDan::integrate(float duration)
{
	if (m_isDead || m_inverseMass <= 0) return;
	
	m_position += m_velocity * duration;

	auto resultingAcceleration = m_acceleration;
	resultingAcceleration += m_forceAccumulator * m_inverseMass;

	m_velocity += resultingAcceleration * duration;

	m_velocity *= powf(m_damping, duration);

	clearAccumulator();
}

void ParticleDan::reset()
{
	m_velocity = glm::vec3{ 0 };
	m_acceleration = glm::vec3{ 0 };
	m_position = m_initialPosition;
}
