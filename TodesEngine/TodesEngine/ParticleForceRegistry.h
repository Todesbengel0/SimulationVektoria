#pragma once
#include <vector>

namespace Todes
{
	class Particle;
	class IParticleForceGenerator;

	/// <summary>
	/// A ParticleForceRegistry contains a set of ParticleForceGenerators and Particles they act on.
	/// </summary>
	class ParticleForceRegistry
	{
#pragma region Registration Entry
	public:
		struct ParticleForceRegistrationEntry
		{
			Particle* m_particle;
			IParticleForceGenerator* m_forceGenerator;
		};
		using Registry_Type = std::vector<ParticleForceRegistrationEntry>;
#pragma endregion

#pragma region Constructor & Destructor
	public:
		explicit ParticleForceRegistry();
		~ParticleForceRegistry();
#pragma endregion

	public:
		/// <summary>
		/// Register a force generator with a particle it acts on.
		/// </summary>
		/// <param name="particle">The particle, which will receive forces.</param>
		/// <param name="generator">The force generator, which will act forces on the particle.</param>
		void add(Particle* particle, IParticleForceGenerator* generator);

		/// <summary>
		/// Register force generators with a particle they act on.
		/// </summary>
		/// <param name="particle">The particle, which will receive forces.</param>
		/// <param name="generator">The force generators, which will act forces on the particle.</param>
		void add(Particle* particle, std::initializer_list<IParticleForceGenerator*> generators);

		/// <summary>
		/// Remove an existing entry.
		/// </summary>
		/// <param name="particle">The particle stored in the entry.</param>
		/// <param name="generator">The force generator stored in the entry.</param>
		/// <returns>TRUE if the given pair was found, FALSE otherwise.</returns>
		bool remove(Particle* particle, IParticleForceGenerator* generator);

		/// <summary>
		/// Removes all Entries of a given particle.
		/// </summary>
		/// <param name="particle">The particle to remove all entries from.</param>
		/// <returns>TRUE: Pairs with this particle were found, FALSE otherwise</returns>
		bool remove(Particle* particle);
		
		/// <summary>
		/// Remove all entries.
		/// </summary>
		void clear();
		
		/// <summary>
		/// Let all registered force generators act forces on their linked particle(s).
		/// </summary>
		void updateForces();

	protected:
		Registry_Type m_registrations;
	};

}

