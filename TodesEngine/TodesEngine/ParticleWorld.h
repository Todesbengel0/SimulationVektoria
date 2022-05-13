#pragma once
#include "PhysicsEngineModule.h"
#include "ParticleForceRegistry.h"
#include "ParticleContactRegistry.h"
#include "FixedSizeContainer.h"

namespace Todes
{
	class Particle;
	class ParticleContact;

	class ParticleWorld : public PhysicsEngineModule
	{
#pragma region Constructor & Destructor
	public:
		explicit ParticleWorld(const unsigned int& maxContacts);
		~ParticleWorld();
#pragma endregion

#pragma region Getter & Setter
	public:
		/// <summary>
		/// Get the module's particle force registry
		/// </summary>
		/// <returns>The particle force registry</returns>
		ParticleForceRegistry& getParticleForceRegistry();

		/// <summary>
		/// Get the module's particle force registry
		/// </summary>
		/// <returns>The particle force registry</returns>
		const ParticleForceRegistry& getParticleForceRegistry() const;

		/// <summary>
		/// Returns the module's Particle Contact Registry
		/// </summary>
		ParticleContactRegistry& getParticleContactRegistry();

		/// <summary>
		/// Returns the module's Particle Contact Registry
		/// </summary>
		const ParticleContactRegistry& getParticleContactRegistry() const;

		/// <summary>
		/// Get the module's particles.
		/// </summary>
		/// <returns>All currently registered particles.</returns>
		std::vector<Particle*>& getParticles();

		/// <summary>
		/// Get the module's particles.
		/// </summary>
		/// <returns>All currently registered particles.</returns>
		const std::vector<Particle*>& getParticles() const;

#pragma endregion

#pragma region Add & Remove Functions
	public:
		/// <summary>
		/// Add an existent particle.
		/// </summary>
		/// <param name="particle">The particle to add.</param>
		void addParticle(Particle* particle);

		/// <summary>
		/// Remove a registered particle.
		/// </summary>
		/// <param name="particle">The particle to remove.</param>
		/// <returns>TRUE: Particle was registered and removed. FALSE: Particle was not registered.</returns>
		bool removeParticle(Particle* particle);
#pragma endregion

#pragma region Engine Functionalities
	public:
		/// <summary>
		/// Updates Particle Forces
		/// </summary>
		void updateForces();

		/// <summary>
		/// Integrates the Particles
		/// </summary>
		/// <param name="timeDelta">Time Step of this update.</param>
		void integrate(const float& timeDelta);

		/// <summary>
		/// Updates Particle Collisions
		/// </summary>
		void updateCollisions();

		/// <summary>
		/// Solves the Particle Collisions
		/// </summary>
		/// <param name="timeDelta">Time Step of this update.</param>
		void solveCollisions(const float& timeDelta);

		/// <summary>
		/// Updates the Particle Forces and Collisions
		/// </summary>
		/// <param name="timeDelta">Time Step of this update.</param>
		void updateWorld(const float& timeDelta);

		/// <summary>
		/// Resets the Particle Contacts
		/// </summary>
		void reset();
#pragma endregion

	private:
		ParticleForceRegistry m_forceRegistry;
		ParticleContactRegistry m_contactRegistry;
		FixedSizeContainer<ParticleContact> m_contactContainer;

		std::vector<Particle*> m_particles;
	};
}

