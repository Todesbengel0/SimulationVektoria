#include "ParticlePlanetGravityForce.h"
#include "Particle.h"

namespace Todes
{

	ParticlePlanetGravityForce::ParticlePlanetGravityForce(Particle* centerOfGravity, const float& gravitationStrength)
		: m_centerOfGravity(centerOfGravity), m_strength(gravitationStrength)
		, m_innerRange(0.0f), m_outerRange(0.0f)
	{ }

	ParticlePlanetGravityForce::~ParticlePlanetGravityForce()
		= default;

	void ParticlePlanetGravityForce::updateForce(Particle* particle)
	{
		if (!particle->hasFiniteMass()) return;

		auto gravity = m_centerOfGravity->getPosition() - particle->getPosition();
		auto length = gravity.Length();
		gravity.Normalize();
		gravity *= m_strength;

		if (m_outerRange > 0.0f)
		{
			if (length > m_outerRange) return;

			if (length > m_innerRange) gravity *= 1.0f - (length - m_innerRange) / (m_outerRange - m_innerRange);
		}

		else if (m_innerRange > 0.0f && length > m_innerRange) return;

		particle->addForce(gravity * particle->getMass());
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

	void ParticlePlanetGravityForce::setInnerRange(const float& innerRange)
	{
		m_innerRange = innerRange;
	}

	void ParticlePlanetGravityForce::setOuterRange(const float& outerRange)
	{
		m_outerRange = outerRange;
	}

}