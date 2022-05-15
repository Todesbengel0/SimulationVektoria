#include "ParticleFloatage.h"
#include "Common.h"
#include "Particle.h"
#include <cassert>

namespace Todes
{

	ParticleFloatage::ParticleFloatage(const float& particleRadius, const float& liquidHeight, const float& liquidDensity /*= 1000.0f*/, const float& liquidViscosity /*= 1.0016f*/, const float& impactConservation /*= 0.7f*/, const float& gravity /*= 9.807f */)
		: m_radius(particleRadius)
		, m_liquidHeight(liquidHeight)
		, m_liquidDensity(liquidDensity)
		, m_liquidViscosity(liquidViscosity)
		, m_impactConservation(impactConservation)
		, m_gravity(gravity)
		, m_impacted(false)
	{ }

	ParticleFloatage::~ParticleFloatage()
		= default;

	void ParticleFloatage::updateForce(Particle* particle)
	{	  
		const auto& particleHeight = particle->getPosition().y();
		auto particleVelocity = particle->getVelocity();

		const auto depth = m_liquidHeight + m_radius - particleHeight;

		// Above water surface
		if (depth <= 0.0f)
		{
			m_impacted = false;
			return;
		}

		if (nearlyEqual(-particle->getAcceleration().y(), m_gravity))
		{
			particle->addForce(Vector3D(0.0f, m_gravity, 0.0f));
			return;
		}

		// The impact with water reduces the velocity of the particle
		if (!m_impacted)
		{
			m_impacted = true;
			particle->setVelocity(particleVelocity *= m_impactConservation);
		}

		const bool isCompletelySubmerged = (depth >= 2.0f * m_radius);

		// Calculate the Volume of the Sphere
		float volume;
		// Volume of the whole Sphere = 4/3 * pi * r³
		if (isCompletelySubmerged)
			volume = FOURTHIRDPI * m_radius * m_radius * m_radius;
		// Volume of cap = d² * (pi * r - 1/3 * pi * d)
		if (!isCompletelySubmerged)
			volume = depth * depth * (PI * m_radius - THIRDPI * depth);
		
		// Buoyancy Force in y direction = p * g * V
		const auto buoyancyForce = Vector3D(0.0f, m_liquidDensity * m_gravity * volume, 0.0f);

		// Drag Force = -1/6 * pi * n * r * v
		const auto dragForce = -SIXPI * m_liquidViscosity * m_radius * particleVelocity;

		particle->addForce(buoyancyForce + dragForce);
	}	  
		  
	const float& ParticleFloatage::getRadius() const
	{	  
		return m_radius;
	}	  
		  
	void ParticleFloatage::setRadius(const float& radius)
	{	  
		m_radius = radius;
	}	  
		  
	const float& ParticleFloatage::getLiquidHeight() const
	{	  
		return m_liquidHeight;
	}	  
		  
	void ParticleFloatage::setLiquidHeight(const float& height)
	{	  
		m_liquidHeight = height;
	}	  
		  
	const float& ParticleFloatage::getLiquidDensity() const
	{	  
		return m_liquidDensity;
	}	  
		  
	void ParticleFloatage::setLiquidDensity(const float& density)
	{	  
		m_liquidDensity = density;
	}	  
		  
	const float& ParticleFloatage::getLiquidViscosity() const
	{
		return m_liquidViscosity;
	}

	void ParticleFloatage::setLiquidViscosity(const float& viscosity)
	{
		m_liquidViscosity = viscosity;
	}

	const float& ParticleFloatage::getImpactConservation() const
	{
		return m_impactConservation;
	}

	void ParticleFloatage::setImpactConservation(const float& conservation)
	{
		m_impactConservation = conservation;
	}

	const float& ParticleFloatage::getGravity() const
	{	  
		return m_gravity;
	}	  
		  
	void ParticleFloatage::setGravity(const float& gravity)
	{
		m_gravity = gravity;
	}

}