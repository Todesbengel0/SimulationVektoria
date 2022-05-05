#pragma once

namespace Todes
{
	class ParticleWorld;
	class Particle;
	class IParticleForceGenerator;
}

class PlacementParticle;

class PlacementParticleWorld
{
#pragma region Using Namespaces
public:
	using ParticleWorld_ptr = std::unique_ptr<Todes::ParticleWorld>;
	using Particles = std::vector<Todes::Particle*>;
	using PlacementParticles = std::vector<PlacementParticle*>;
	using ForceGeneratorList = std::initializer_list<Todes::IParticleForceGenerator*>;
#pragma endregion

#pragma region Constructor & Destructor
public:
	explicit PlacementParticleWorld();
	~PlacementParticleWorld();
#pragma endregion

#pragma region Getter & Setter
public:
	/// <summary>
	/// Returns all registered particles.
	/// </summary>
	/// <returns>Constant Container of Particles</returns>
	const Particles& getParticles() const;

	/// <summary>
	/// Returns all registered particles.
	/// </summary>
	/// <returns>Adjustable Container of Particles.</returns>
	Particles& getParticles();

	/// <summary>
	/// Returns the pointer to the particle world.
	/// </summary>
	Todes::ParticleWorld* getWorld() const;
#pragma endregion

#pragma region Add & Remove Functions
	/// <summary>
	/// Adds a new Placement Particle.
	/// </summary>
	/// <param name="placement">Placement Particle to add.</param>
	void addPlacementParticle(PlacementParticle* placement);

	/// <summary>
	/// Adds a new Placement Particle with Force Generators for the Particle.
	/// </summary>
	/// <param name="placement">Placement Particle to add.</param>
	/// <param name="generators">Force Generators that act on the Particle.</param>
	void addPlacementParticle(PlacementParticle* placement, ForceGeneratorList generators);

	/// <summary>
	/// Adds Force Generators to act on a registered Particle.
	/// </summary>
	/// <param name="placement">Placement Particle on which the Force should act on.</param>
	/// <param name="generators">Force Generators that act on the Particle.</param>
	/// <returns>TRUE: Placement was registered. FALSE: Placement was not registered.</returns>
	bool addForces(PlacementParticle* placement, ForceGeneratorList generators);

	/// <summary>
	/// Removes an already registered Placement Particle.
	/// </summary>
	/// <param name="placement">Placement Particle to remove.</param>
	/// <returns>TRUE: Placement was registered and removed. FALSE: Placement was not registered.</returns>
	bool removePlacementParticle(PlacementParticle* placement);

	/// <summary>
	/// Deletes an already registered Placement Particle.
	/// </summary>
	/// <param name="placement">Placement Particle to delete.</param>
	/// <returns>TRUE: Placement was registered and deleted. FALSE: Placement was not registered.</returns>
	bool deletePlacementParticle(PlacementParticle* placementParticle);

	/// <summary>
	/// Clears the list of Placement Particles.
	/// </summary>
	void clear();
#pragma endregion

public:
	/// <summary>
	/// Update all Placement Particles.
	/// </summary>
	void update(float timeDelta);

	/// <summary>
	/// Resets the Placement Particles
	/// </summary>
	void reset() const;

	/// <summary>
	/// Kills the Placement Particles
	/// </summary>
	void kill() const;

	void revive() const;

private:
	PlacementParticles m_placementParticles;
	ParticleWorld_ptr m_world;
};

