#include "ParticleContactRegistry.h"
#include "IParticleContactGenerator.hpp"
#include <cassert>

namespace Todes
{
	ParticleContactRegistry::ParticleContactRegistry()
		= default;

	ParticleContactRegistry::~ParticleContactRegistry()
		= default;

	void ParticleContactRegistry::add(IParticleContactGenerator* generator)
	{
		m_contactGenerators.push_back(generator);
	}

	void ParticleContactRegistry::add(const std::initializer_list<IParticleContactGenerator*>& generators)
	{
		m_contactGenerators.insert(m_contactGenerators.end(), generators.begin(), generators.end());
	}

	bool ParticleContactRegistry::remove(IParticleContactGenerator* generator)
	{
		auto endIt = m_contactGenerators.end();
		auto removeIt = std::remove(m_contactGenerators.begin(), endIt, generator);
		
		if (removeIt == endIt)
			return false;

		m_contactGenerators.erase(removeIt, endIt);
		return true;
	}

	void ParticleContactRegistry::clear()
	{
		m_contactGenerators.clear();
	}

	const ParticleContactRegistry::ContactGeneratorContainer& ParticleContactRegistry::get() const
	{
		return m_contactGenerators;
	}

	ParticleContactRegistry::ContactGeneratorContainer::const_iterator ParticleContactRegistry::begin() const
	{
		return m_contactGenerators.begin();
	}

	ParticleContactRegistry::ContactGeneratorContainer::const_iterator ParticleContactRegistry::end() const
	{
		return m_contactGenerators.end();
	}

	std::size_t ParticleContactRegistry::size() const
	{
		return m_contactGenerators.size();
	}

	Todes::IParticleContactGenerator* ParticleContactRegistry::operator[](const std::size_t& index)
	{
		assert(index < m_contactGenerators.size());
		return m_contactGenerators[index];
	}

}