#include "ParticleGravityForce.h"
#include "Particle.h"


namespace Todes
{
	ParticleGravityForce::ParticleGravityForce(const Vector3D& gravity)
		: m_gravity(gravity)
	{ }

	ParticleGravityForce::~ParticleGravityForce()
		= default;

	void ParticleGravityForce::updateForce(Particle* particle)
	{
		if (!particle->hasFiniteMass()) return;

		particle->addForce(m_gravity * particle->getMass());
	}

	const Vector3D& ParticleGravityForce::getGravity() const
	{
		return m_gravity;
	}

	void ParticleGravityForce::setGravity(const Vector3D& gravity)
	{
		m_gravity = gravity;
	}
}