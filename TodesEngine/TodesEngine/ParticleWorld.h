#pragma once
#include "PhysicsEngineModule.h"
#include "ParticleForceRegistry.h"

namespace Todes
{
	class Particle;

	class ParticleEngineCI;

	class ParticleWorld : public PhysicsEngineModule
	{
#pragma region Constructor & Destructor
	public:
		explicit ParticleWorld();
		~ParticleWorld();
#pragma endregion

#pragma region Getter & Setter
	public:
		/// <summary>
		/// Change the computation interface, used by the module.
		/// </summary>
		/// <param name="computationInterface">The new computation interface.</param>
		void setComputationInterface(ParticleEngineCI* computationInterface);

		/// <summary>
		/// Get the module's computation interface.
		/// </summary>
		/// <returns>The currently used computation interface.</returns>
		IComputationInterface* getComputationInterface() const override;

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

	private:
		ParticleEngineCI* m_computationInterface{};

		ParticleForceRegistry m_forceRegistry;

		std::vector<Particle*> m_particles;
	};
}

