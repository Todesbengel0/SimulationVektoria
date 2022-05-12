#pragma once
#include "IParticleContactGenerator.hpp"

namespace Todes
{
    class Particle;
    class ParticleContact;

    /// <summary>
    /// Abstract Class for linking two particles
    /// </summary>
    class ParticleLink : public IParticleContactGenerator
    {
	public:
		virtual ~ParticleLink();

		/// <summary>
		/// Sets the referenced particles.
		/// </summary>
		void setParticles(Particle* first, Particle* second);

		/// <summary>
		/// Returns the first particle.
		/// </summary>
		Particle* getFirst() const;

		/// <summary>
		/// Returns the second particle.
		/// </summary>
		Particle* getSecond() const;

	protected:
		explicit ParticleLink();

		/// <summary>
		/// Calculates the length between the current particles.
		/// </summary>
		/// <returns>Length between the particles.</returns>
		float currentLength() const;


	protected:
		Particle* m_particles[2];
	};

}