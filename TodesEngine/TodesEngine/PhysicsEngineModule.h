#pragma once
#include <iostream>
#include <vector>

namespace Todes
{
	class IComputationInterface;

	/// <summary>
	/// Abstract class for physic engine modules.
	/// </summary>
	class PhysicsEngineModule
	{
	public:
		virtual ~PhysicsEngineModule();
		
		/// <summary>
		/// Get the computation interface of this module.
		/// </summary>
		/// <returns>The computation interface.</returns>
		virtual IComputationInterface* getComputationInterface() const = 0;

		/// <summary>
		/// Enable or disable this module.
		/// </summary>
		/// <param name="enabled">True will enable it, false disable it.</param>
		void enable(const bool& enabled = true);

		/// <summary>
		/// Check if this module is currently enabled.
		/// </summary>
		/// <returns>True if enabled, false otherwise.</returns>
		const bool& isEnabled() const;

	protected:
		explicit PhysicsEngineModule();

		bool m_isEnabled;
	};
}
