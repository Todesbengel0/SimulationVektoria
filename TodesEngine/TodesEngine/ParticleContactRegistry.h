#pragma once
#include <iostream>
#include <vector>

namespace Todes
{
	class IParticleContactGenerator;

	/// <summary>
	/// Registry for Particle Contact Generators
	/// </summary>
	class ParticleContactRegistry
	{
	public:
		using ContactGeneratorContainer = std::vector<IParticleContactGenerator*>;

	public:
		explicit ParticleContactRegistry();
		~ParticleContactRegistry();

		/// <summary>
		/// Registers a Particle Contact Generator
		/// </summary>
		void add(IParticleContactGenerator* generator);

		/// <summary>
		/// Registers a variable number of Particle Contact Generators
		/// </summary>
		void add(const std::initializer_list<IParticleContactGenerator*>& generators);

		/// <summary>
		/// Removes a contact generator
		/// </summary>
		/// <param name="generator">The generator to remove</param>
		/// <returns>TRUE: Generator was found and removed. FALSE: Generator is not registered.</returns>
		bool remove(IParticleContactGenerator* generator);

		/// <summary>
		/// Removes all Contact Generators from this registry.
		/// </summary>
		void clear();

		/// <summary>
		/// Returns all generators from this registry
		/// </summary>
		/// <returns></returns>
		const ContactGeneratorContainer& get() const;

		/// <summary>
		/// Returns an iterator onto the first element in the registry.
		/// </summary>
		ContactGeneratorContainer::const_iterator begin() const;

		/// <summary>
		/// Returns an iterator behind the last element in the registry.
		/// </summary>
		ContactGeneratorContainer::const_iterator end() const;

		/// <summary>
		/// Returns the number of Contact Generators in the Registry
		/// </summary>
		std::size_t size() const;

		IParticleContactGenerator* operator[](const std::size_t& index);

	protected:
		ContactGeneratorContainer m_contactGenerators;
	};

}