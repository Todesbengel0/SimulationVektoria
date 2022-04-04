#pragma once
#include <glm/glm.hpp>

class ParticleDan
{
public:
	ParticleDan(glm::vec3 position, float damping, float inverseMass);

public:
	void setMass(float mass);
	void setInverseMass(float inverseMass);
	void sendDeath(bool isDead = true);
	float getMass() const;
	bool isDead() const;
	glm::vec3 getPosition() const;

	void clearAccumulator();
	void addForce(const glm::vec3& force);

	virtual void integrate(float duration);
	void reset();

protected:
	glm::vec3 m_position;
	glm::vec3 m_initialPosition;
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;

	glm::vec3 m_forceAccumulator;
	float m_damping;
	float m_inverseMass;

	bool m_isDead;
};

