#pragma once
#include "FixedSizeContainer.h"

namespace Todes
{
	class ParticleContact;

	/// <summary>
	/// Interface for contact generators for particles.
	/// </summary>
	class IParticleContactGenerator
	{
	public:
		virtual ~IParticleContactGenerator() = default;

		/// <summary>
		/// Adds new contacts.
		/// </summary>
		/// <param name="contactData">Out parameter in which new contacts are added.</param>
		virtual void addContact(FixedSizeContainer<ParticleContact>& contactData) const = 0;

	protected:
		explicit IParticleContactGenerator() = default;
	};

}