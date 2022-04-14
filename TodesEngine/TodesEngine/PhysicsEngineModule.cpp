#include "PhysicsEngineModule.h"

namespace Todes
{
	PhysicsEngineModule::PhysicsEngineModule()
		: m_isEnabled(true)
	{

	}

	PhysicsEngineModule::~PhysicsEngineModule()
		= default;

	void PhysicsEngineModule::enable(const bool& enabled /*= true*/)
	{
		m_isEnabled = enabled;
	}

	const bool& PhysicsEngineModule::isEnabled() const
	{
		return m_isEnabled;
	}

}
