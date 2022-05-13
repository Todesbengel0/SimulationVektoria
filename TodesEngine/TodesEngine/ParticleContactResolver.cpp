#include "ParticleContactResolver.h"
#include "ParticleContact.h"
#include "Particle.h"
#include <limits>

namespace Todes
{
	
	void ParticleContactResolver::ResolveContacts(FixedSizeContainer<ParticleContact>& contactData, const unsigned int& maxIterations, const float& timeDelta)
	{
		const auto& contactCount = contactData.getUsedEntries();

		unsigned int iterationsUsed = 0;

		while (iterationsUsed < maxIterations)
		{
			// Search for contact with smallest separation velocity (greatest collision velocity)
			auto max = std::numeric_limits<float>::max();
			auto maxIndex = contactCount;

			for (unsigned int i = 0; i < contactCount; ++i)
			{
				auto& currentContact = contactData[i];

				const auto separationVelocity = currentContact.CalculateSeparatingVelocity();

				if (separationVelocity < max &&
					(separationVelocity < 0.0f || currentContact.getPenetration() > 0.0f))
				{
					max = separationVelocity;
					maxIndex = i;
				}
			}

			// We break if there is nothing to calculate
			if (maxIndex == contactCount) break;

			// Resolve the Contact the smallest separation velocity
			auto& mostImportantContact = contactData[maxIndex];
			mostImportantContact.resolve(timeDelta);

			// Calculate Penetration
			auto micFirst = mostImportantContact.getFirst();
			auto micSecond = mostImportantContact.getSecond();
			const auto move = mostImportantContact.getParticlesMovement();

			for (unsigned i = 0; i < contactCount; ++i)
			{
				auto& currentContact = contactData[i];

				auto currFirst = currentContact.getFirst();
				auto currSecond = currentContact.getSecond();
				const auto& contactNormal = currentContact.getContactNormal();

				if (!currSecond->hasFiniteMass())
				{
					if (currFirst == micFirst)
						currentContact.AddPenetration(-move[0] * contactNormal);

					else if (currFirst == micSecond)
						currentContact.AddPenetration(-move[1] * contactNormal);
				}
			}

			++iterationsUsed;
		}


	}


}