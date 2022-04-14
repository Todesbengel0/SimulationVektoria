#pragma once

namespace Todes
{
	class ParticleWorld;
	class Particle;
}

class PlacementParticle;

class PlacementParticleWorld
{
#pragma region Using Namespaces
public:
	using ParticleWorld_ptr = std::unique_ptr<Todes::ParticleWorld>;
	using Particles = std::vector<Todes::Particle*>;
	using PlacementParticles = std::vector<PlacementParticle*>;
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
	/// Removes an already registered Placement Particle.
	/// </summary>
	/// <param name="placement">Placement Particle to remove.</param>
	/// <returns>TRUE: Placement was registered and removed. FALSE: Placement was not registered.</returns>
	bool removePlacementParticle(PlacementParticle* placement);

	/// <summary>
	/// Clears the list of Placement Particles.
	/// </summary>
	void clear();
#pragma endregion

public:
	/// <summary>
	/// Update all Placement Particles.
	/// </summary>
	void update();

private:
	PlacementParticles m_placementParticles;
	ParticleWorld_ptr m_world;
};

