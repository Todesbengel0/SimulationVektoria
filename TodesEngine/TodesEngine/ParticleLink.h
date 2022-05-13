#pragma once
#include "IParticleContactGenerator.hpp"

namespace Todes
{
    class Particle;
    class ParticleContact;

    /// <summary>
    /// Abstract Class for linking two particles
    /// </summary>
    class ParticleLink : public IParticleContactGenerator
    {
	public:
		virtual ~ParticleLink();

		/// <summary>
		/// Sets the referenced particles.
		/// </summary>
		void setParticles(Particle* first, Particle* second);

		/// <summary>
		/// Generates new Contacts.
		/// </summary>
		/// <param name="contactData">Out parameter in which new contacts are added.</param>
		void addContact(FixedSizeContainer<ParticleContact>& contactData) const override;

		/// <summary>
		/// Calculates the penetration between the two particles.
		/// </summary>
		virtual float calculatePenetration() const = 0;

		/// <summary>
		/// Returns the first particle.
		/// </summary>
		Particle* getFirst() const;

		/// <summary>
		/// Returns the second particle.
		/// </summary>
		Particle* getSecond() const;

		/// <summary>
		/// Sets the restitution of the generated contacts.
		/// </summary>
		/// <param name="restitution">Restitution coefficient [unitless quantity].</param>
		void setRestitution(const float& restitution);

		/// <summary>
		/// Sets the threshold at which contacts will be generated.
		/// </summary>
		/// <param name="distance">Distance at which to calculate Contact.</param>
		void setTriggerDistance(const float& distance);

	protected:
		explicit ParticleLink(const float& triggerDistance = 1.0f, const float& restitution = 0.0f);

		/// <summary>
		/// Calculates the length between the current particles.
		/// </summary>
		/// <returns>Length between the particles.</returns>
		float currentLength() const;


	protected:
		Particle* m_particles[2];
		float m_triggerDistance;
		float m_restitution;
	};

}