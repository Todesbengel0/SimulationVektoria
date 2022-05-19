#pragma once
#include "Vector3D.h"

namespace Todes
{
	class Particle
	{
	public:
		Particle();
		Particle(const Vector3D& position, const float& damping, const float& inverseMass);

	public:
		void setMass(const float& mass);
		void setInverseMass(const float& inverseMass);
		void sendDeath(const bool& isDead = true);
		void setVelocity(const Vector3D& velocity);
		void addVelocity(const Vector3D& velocitySummand);
		void addCurrentAcceleration(const Vector3D& accelerationSummand);
		void setBaseAcceleration(const Vector3D& acceleration);
		void setPosition(const Vector3D& position);
		void translate(const Vector3D& translationVector);
		float getMass() const;
		const float& getInverseMass() const;
		const bool& isDead() const;
		const bool hasFiniteMass() const;
		const Vector3D& getVelocity() const;
		const Vector3D& getBaseAcceleration() const;
		const Vector3D& getCurrentAcceleration() const;
		const Vector3D& getPosition() const;

		void clearAccumulator();
		void addForce(const Vector3D& force);

		virtual void integrate(float duration);
		void reset();

	protected:
		Vector3D m_position;
		Vector3D m_initialPosition;
		Vector3D m_velocity;
		Vector3D m_baseAcceleration;
		Vector3D m_currentAcceleration;

		Vector3D m_forceAccumulator;
		float m_damping;
		float m_inverseMass;

		bool m_isDead;
	};
}
