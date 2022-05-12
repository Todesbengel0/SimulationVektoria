#include "ParticleFloatage.h"
#include "Particle.h"

#include <cassert>

namespace Todes
{

	ParticleFloatage::ParticleFloatage(const float& maxDepth, const float& volume, const float& liquidHeight, const float& liquidDensity /*= 1000.0f*/, const float& gravity /*= 9.807f */)
		: m_volume(volume)
		, m_liquidHeight(liquidHeight)
		, m_liquidDensity(liquidDensity)
		, m_gravity(gravity)
	{
		setMaxDepth(maxDepth);
	}

	ParticleFloatage::~ParticleFloatage()
		= default;

	void ParticleFloatage::updateForce(Particle* particle)
	{	  
		const auto& depth = particle->getPosition().y();
		const auto halfMaxDepth = m_maxDepth * 0.5f;

		// Above water surface
		if (depth >= m_liquidHeight + halfMaxDepth)
			return;

		// Completely submerged
		const auto verticalForce = m_liquidDensity * m_volume * m_gravity;

		Vector3D force;

		if (depth <= m_liquidHeight - halfMaxDepth)
		{
			force.y(verticalForce);
			particle->addForce(force);
			return;
		}

		// Partly submerged
		const auto submergedDistance = m_liquidHeight + halfMaxDepth - depth;
		force.y(verticalForce * submergedDistance / m_maxDepth);
		particle->addForce(force);
	}	  
		  
	float ParticleFloatage::getMaxDepth() const
	{	  
		return m_maxDepth;
	}	  
		  
	void ParticleFloatage::setMaxDepth(const float& depth)
	{	  
		assert(depth != 0.0f);
		m_maxDepth = depth;
	}	  
		  
	float ParticleFloatage::getVolume() const
	{	  
		return m_volume;
	}	  
		  
	void ParticleFloatage::setVolume(const float& volume)
	{	  
		m_volume = volume;
	}	  
		  
	float ParticleFloatage::getLiquidHeight() const
	{	  
		return m_liquidHeight;
	}	  
		  
	void ParticleFloatage::setLiquidHeight(const float& height)
	{	  
		m_liquidHeight = height;
	}	  
		  
	float ParticleFloatage::getLiquidDensity() const
	{	  
		return m_liquidDensity;
	}	  
		  
	void ParticleFloatage::setLiquidDensity(const float& density)
	{	  
		m_liquidDensity = density;
	}	  
		  
	float ParticleFloatage::getGravity() const
	{	  
		return m_gravity;
	}	  
		  
	void ParticleFloatage::setGravity(const float& gravity)
	{
		m_gravity = gravity;
	}

}