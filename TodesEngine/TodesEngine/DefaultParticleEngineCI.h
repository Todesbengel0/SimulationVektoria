#pragma once
#include "ParticleEngineCI.h"

namespace Todes
{

    class DefaultParticleEngineCI : public ParticleEngineCI
    {
	public:
		explicit DefaultParticleEngineCI(ParticleWorld* particleWorld = nullptr);
		~DefaultParticleEngineCI();

		void onBegin() override;

		/// <summary>
		/// Update particle forces.
		/// </summary>
		/// <param name="timeDelta">Time step of this update.</param>
		void step(float timeDelta) override;

		/// <summary>
		/// Perform integration and solve collisions.
		/// </summary>
		/// <param name="timeDelta">Time step of this update.</param>
		void integrate(float timeDelta) override;

		/// <summary>
		/// Clear force accumulators and reset contact data.
		/// </summary>
		void onEnd() override;

		/// <summary>
		/// Reset the computation interface.
		/// </summary>
		void reset() override;
    };

}