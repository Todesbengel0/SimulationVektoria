#include "ParticlePlanetGravityForce.h"
#include "Particle.h"
#include <cassert>

namespace Todes
{

	ParticlePlanetGravityForce::ParticlePlanetGravityForce(Particle* centerOfGravity, const float& gravitationStrength)
		: m_centerOfGravity(centerOfGravity), m_inverseConstant(1.0f / gravitationStrength)
		, m_innerRangeSq(0.0f), m_outerRangeSq(0.0f)
	{ }

	ParticlePlanetGravityForce::ParticlePlanetGravityForce(Particle* centerOfGravity)
		: m_centerOfGravity(centerOfGravity)
		, m_inverseConstant(14983518130.1f)
		, m_innerRangeSq(0.0f), m_outerRangeSq(0.0f)
	{ }

	ParticlePlanetGravityForce::~ParticlePlanetGravityForce()
		= default;

	void ParticlePlanetGravityForce::updateForce(Particle* particle)
	{
		if (!particle->hasFiniteMass()) return;

		auto gravity = m_centerOfGravity->getPosition() - particle->getPosition();
		auto distanceSquared = gravity.LengthSq();
		gravity.Normalize();

		if (m_outerRangeSq > 0.0f && distanceSquared > m_outerRangeSq) return;
		
		if (distanceSquared < m_innerRangeSq) distanceSquared = m_innerRangeSq;

		auto inverseForce = particle->getInverseMass() * m_centerOfGravity->getInverseMass()
			* m_inverseConstant * distanceSquared;

		particle->addForce(gravity / inverseForce);
	}

	Particle* ParticlePlanetGravityForce::getCenterOfGravity()
	{
		return m_centerOfGravity;
	}

	void ParticlePlanetGravityForce::setCenterOfGravity(Particle* newCenter)
	{
		m_centerOfGravity = newCenter;
	}

	const float ParticlePlanetGravityForce::getGravitationConstant() const
	{
		assert(m_inverseConstant > 0.0f);
		return 1.0f / m_inverseConstant;
	}

	void ParticlePlanetGravityForce::setInnerRange(const float& innerRange)
	{
		m_innerRangeSq = innerRange * innerRange;
	}

	void ParticlePlanetGravityForce::setOuterRange(const float& outerRange)
	{
		m_outerRangeSq = outerRange * outerRange;
	}

}