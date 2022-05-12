#include "ParticleTyphoon.h"
#include "Particle.h"
#include "Random.h"
#include <cassert>
constexpr auto TWOPI = 6.28318530718f;

namespace Todes
{

	ParticleTyphoon::ParticleTyphoon(
		const float& particleHalfHeight,
		const std::initializer_list<CalmSpace>& calmSpaces,
		const float& minStrength,
		const float& maxStrength,
		const float& maxDifference /*= QUATERPI*/,
		const float& chaosChance /*= 0.0f */,
		const float& calmResistance /*= 0.0f*/)
		: m_calmResistance(calmResistance)
	{
		for (auto& calmSpace : calmSpaces)
			addCalmSpace(calmSpace);
	
		assert(particleHalfHeight >= 0.0f);
		m_particleHalfHeight = particleHalfHeight;

		assert(0.0f <= minStrength && minStrength <= maxStrength);
		m_minStrength = minStrength;
		m_maxStrength = maxStrength;

		assert(0.0f <= maxDifference);
		m_maxDifference = maxDifference;

		assert(0.0f <= chaosChance && chaosChance <= 1.0f);
		m_chaosChance = chaosChance;

		Random::seed();
	}

	ParticleTyphoon::~ParticleTyphoon()
		= default;

	void ParticleTyphoon::updateForce(Particle* particle)
	{
		const auto& particlePosition = particle->getPosition();
		const float particleRight = particlePosition.x() + m_particleHalfHeight;
		const float particleLeft = particlePosition.x() - m_particleHalfHeight;
		const float particleBack = particlePosition.z() - m_particleHalfHeight;
		const float particleFront = particlePosition.z() + m_particleHalfHeight;
		const float particleUp = particlePosition.y() + m_particleHalfHeight;
		const float particleDown = particlePosition.y() - m_particleHalfHeight;

		for (const auto& calmSpace : m_calmSpaces)
		{
			const float& calmLeft = calmSpace.calmOrigin.x();
			const float& calmDown = calmSpace.calmOrigin.y();
			const float& calmBack = calmSpace.calmOrigin.z();
			const float calmRight = calmSpace.calmDimensions.x() + calmLeft;
			const float	calmUp    = calmSpace.calmDimensions.y() + calmDown;
			const float calmFront = calmSpace.calmDimensions.z() + calmBack;

			// Check for no overlap
			if (
				particleLeft > calmRight
				|| particleRight < calmLeft
				|| particleFront < calmBack
				|| particleBack > calmFront
				|| particleUp < calmDown
				|| particleDown > calmUp
			)	continue;
			
			if (m_calmResistance != 0.0f)
				particle->addForce(-particle->getVelocity() * m_calmResistance);

			m_currentDirection = Vector3D();
			return;
		}

		// Calculate new Wind Direction
		if (m_currentDirection.LengthSq() == 0.0f || Random::Bool(m_chaosChance))
		{
			m_currentDirection = Vector3D(1.0f, 0.0f, 0.0f);
			m_currentDirection.RotateY(Random::FloatNorm() * TWOPI);
		}
		// Rotate Wind Direction
		else
		{
			const auto halfDif = m_maxDifference * 0.5f;
			m_currentDirection.RotateY(Random::Float(-halfDif, halfDif));
		}

		// Calculate Strength
		particle->addForce(m_currentDirection * Random::Float(m_minStrength, m_maxStrength));
	}

	const float& ParticleTyphoon::getHalfHeight() const
	{
		return m_particleHalfHeight;
	}

	const std::vector<Todes::CalmSpace>& ParticleTyphoon::getCalmSpaces() const
	{
		return m_calmSpaces;
	}

	const float& ParticleTyphoon::getMinStrength() const
	{
		return m_minStrength;
	}

	const float& ParticleTyphoon::getMaxStrength() const
	{
		return m_maxStrength;
	}

	const float& ParticleTyphoon::getMaxDifference() const
	{
		return m_maxDifference;
	}

	const float& ParticleTyphoon::getChaosChance() const
	{
		return m_chaosChance;
	}

	const float& ParticleTyphoon::getCalmResistance() const
	{
		return m_calmResistance;
	}

	void ParticleTyphoon::setHalfHeight(const float& particleHalfHeight)
	{
		assert(particleHalfHeight >= 0.0f);
		m_particleHalfHeight = particleHalfHeight;
	}

	bool ParticleTyphoon::setCalmSpace(const CalmSpace& whatSpace, const CalmSpace& toSpace)
	{
		const auto vectorEnd = m_calmSpaces.end();
		const auto it = std::find(m_calmSpaces.begin(), vectorEnd, whatSpace);

		if (it == vectorEnd)
			return false;

		(*it) = toSpace;
		return true;
	}

	void ParticleTyphoon::addCalmSpace(const CalmSpace& calmSpace)
	{
		CalmSpace newSpace = calmSpace;

		if (calmSpace.calmDimensions.x() < 0.0f)
		{
			newSpace.calmOrigin.x(calmSpace.calmOrigin.x() + calmSpace.calmDimensions.x());
			newSpace.calmDimensions.x(-calmSpace.calmDimensions.x());
		}
		if (calmSpace.calmDimensions.y() < 0.0f)
		{
			newSpace.calmOrigin.y(calmSpace.calmOrigin.y() + calmSpace.calmDimensions.y());
			newSpace.calmDimensions.y(-calmSpace.calmDimensions.y());
		}
		if (calmSpace.calmDimensions.z() < 0.0f)
		{
			newSpace.calmOrigin.z(calmSpace.calmOrigin.z() + calmSpace.calmDimensions.z());
			newSpace.calmDimensions.z(-calmSpace.calmDimensions.z());
		}

		m_calmSpaces.push_back(newSpace);
	}

	bool ParticleTyphoon::removeCalmSpace(const CalmSpace& calmSpace)
	{
		const auto vectorEnd = m_calmSpaces.end();
		const auto it = std::find(m_calmSpaces.begin(), vectorEnd, calmSpace);

		if (it == vectorEnd)
			return false;

		m_calmSpaces.erase(it);
		return true;
	}

	void ParticleTyphoon::setStrength(const float& minStrength, const float& maxStrength)
	{
		assert(0.0f <= minStrength && minStrength <= maxStrength);
		m_minStrength = minStrength;
		m_maxStrength = maxStrength;
	}

	void ParticleTyphoon::setMaxDifference(const float& maxDifference)
	{
		assert(0.0f <= maxDifference);
		m_maxDifference = maxDifference;
	}

	void ParticleTyphoon::setChaosChance(const float& chaosChance)
	{
		assert(0.0f <= chaosChance && chaosChance <= 1.0f);
		m_chaosChance = chaosChance;
	}

	void ParticleTyphoon::setCalmResistance(const float& calmResistance)
	{
		m_calmResistance = calmResistance;
	}

}