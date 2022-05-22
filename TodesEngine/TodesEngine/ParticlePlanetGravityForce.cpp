#include "ParticlePlanetGravityForce.h"
#include "Particle.h"

namespace Todes
{

	ParticlePlanetGravityForce::ParticlePlanetGravityForce(Particle* centerOfGravity, const float& gravitationStrength)
		: m_centerOfGravity(centerOfGravity), m_strength(gravitationStrength)
	{ }

	ParticlePlanetGravityForce::~ParticlePlanetGravityForce()
		= default;

	void ParticlePlanetGravityForce::updateForce(Particle* particle)
	{

	}

	Particle* ParticlePlanetGravityForce::getCenterOfGravity()
	{
		return m_centerOfGravity;
	}

	void ParticlePlanetGravityForce::setCenterOfGravity(Particle* newCenter)
	{
		m_centerOfGravity = newCenter;
	}

	const float& ParticlePlanetGravityForce::getGravitationStrength() const
	{
		return m_strength;
	}

	void ParticlePlanetGravityForce::setGravitationStrength(const float& newStrength)
	{
		m_strength = newStrength;
	}

}