#pragma once
#include "FixedSizeContainer.h"

namespace Todes
{
	class ParticleContact;

	/// <summary>
	/// Static Class for resolving a given number of Contacts
	/// </summary>
	class ParticleContactResolver
	{
	public:
		/// <summary>
		/// Resolves the contacts.
		/// </summary>
		/// <param name="contactData">The contacts to be resolved.</param>
		/// <param name="maxIterations">Maximum number of iterations for the Resolver.</param>
		/// <param name="timeDelta">Time difference from this update to the last.</param>
		static void ResolveContacts(FixedSizeContainer<ParticleContact>& contactData
			, const unsigned int& maxIterations
			, const float& timeDelta);

	protected:
		explicit ParticleContactResolver() = default;
		~ParticleContactResolver() = default;
	};

}