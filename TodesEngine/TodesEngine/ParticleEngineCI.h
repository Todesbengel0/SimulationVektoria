#pragma once
#include "IComputationInterface.h"

namespace Todes
{
    class ParticleWorld;

    class ParticleEngineCI : public IComputationInterface
    {
	public:
		virtual ~ParticleEngineCI();

		/// <summary>
		/// Set the particle world, used for particle calculations.
		/// </summary>
		/// <param name="particleWorld">particleWorld The particle world, which should be used for calculations.< / param>
		void setParticleWorld(ParticleWorld* particleWorld);

		/// <summary>
		/// Get the particle world.
		/// </summary>
		/// <returns>The currently used particle world.</returns>
		ParticleWorld* getParticleWorld() const;

	protected:
		/// <summary>
		/// ParticleEngineCI constructor
		/// </summary>
		/// <param name="particleWorld">The particle world, which should be used for calculations.< / param>
		explicit ParticleEngineCI(ParticleWorld* particleWorld = nullptr);

		ParticleWorld* m_particleWorld;
    };
}
