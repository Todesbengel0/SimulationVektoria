#pragma once

namespace Todes
{
	class IComputationInterface
	{
	public:
		virtual ~IComputationInterface() = default;

	public:
		/// <summary>
		/// Called at the start of a physics step.
		/// </summary>
		virtual void onBegin() = 0;

		/// <summary>
		/// Used to calculate changes.
		/// </summary>
		/// <param name="timeDelta">The time step of the physics step.</param>
		virtual void step(float timeDelta) = 0;

		/// <summary>
		/// Used to apply changes.
		/// </summary>
		/// <param name="timeDelta">The time step of the physics step.</param>
		virtual void integrate(float timeDelta) = 0;

		/// <summary>
		/// Called at the end of a physics step.
		/// </summary>
		virtual void onEnd() = 0;

		/// <summary>
		/// Resets a computation interface to its start state.
		/// </summary>
		virtual void reset() = 0;

	protected:
		explicit IComputationInterface() = default;
	};
}

