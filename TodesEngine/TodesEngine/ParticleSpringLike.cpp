#include "ParticleSpringLike.h"
#include "Vector3D.h"
#include "Particle.h"

Todes::ParticleSpringLike::ParticleSpringLike(const float& springConstant, const float& restLength)
	: m_springConstant(springConstant),
	m_restLength(restLength)
{ }

void Todes::ParticleSpringLike::updateForce(Particle* particle)
{
	auto force = particle->getPosition();
	force -= getOtherEnd();

	auto magnitude = calculateMagnitude(force);

	if (magnitude == 0.0f)
		return;

	force.Normalize();
	force *= magnitude;
	particle->addForce(force);
}

float Todes::ParticleSpringLike::calculateMagnitude(const Vector3D& force) const
{
	auto magnitude = force.Length();

	if (magnitude == 0.0f)
		return 0.0f;

	magnitude -= m_restLength;
	magnitude *= m_springConstant;

	return -magnitude;
}
