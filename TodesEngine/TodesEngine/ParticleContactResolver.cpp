#include "ParticleContactResolver.h"
#include "ParticleContact.h"
#include "Particle.h"
#include <limits>

namespace Todes
{
	
	void ParticleContactResolver::ResolveContacts(FixedSizeContainer<ParticleContact>& contactData, const unsigned int& maxIterations, const float& timeDelta)
	{
		const auto& contactCount = contactData.getUsedEntries();

		for (unsigned int iterationsUsed = 0; iterationsUsed < maxIterations; ++iterationsUsed)
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
			const auto move = mostImportantContact.resolve(timeDelta);

			if (move.first.isNull()) return;

			// If the Resolve has created a new interpenetration (or reduced one),
			// we need to resolve it in a later iteration
			auto maxFirst = contactData[maxIndex].getFirst();
			auto maxSecond = contactData[maxIndex].getSecond();

			for (unsigned i = 0; i < contactCount; ++i)
			{
				if (i == maxIndex)
					continue;

				auto currFirst = contactData[i].getFirst();
				auto currSecond = contactData[i].getSecond();

				const auto& contactNormal = contactData[i].getContactNormal();

				// If our first particle from the last calculation is 
				// the first particle of this contact,
				// we need to subtract its Translation away from contact normal
				if (maxFirst == currFirst)
					contactData[i].AddPenetration(-move.first * contactNormal);
				// If it is the second particle of this contact,
				// we want to add the Translation away from contact normal
				else if (maxFirst == currSecond)
					contactData[i].AddPenetration(move.first * contactNormal);

				if (move.second.isNull()) continue;

				// If our second particle from the last calculation is 
				// the first particle of this contact,
				if (maxFirst == currFirst)
					contactData[i].AddPenetration(-move.second * contactNormal);
				// If it is the second particle of this contact,
				// we want to add the Translation away from contact normal
				else if (maxFirst == currSecond)
					contactData[i].AddPenetration(move.second * contactNormal);
			}

		}
	}


}