#pragma once
#include "ParticleLink.h"

namespace Todes
{
    class ParticleContact;

    /// <summary>
    /// Contact Generator that generates a contact if the two particles are too far apart.
    /// </summary>
    class ParticleCable : public ParticleLink
    {
	public:
		/// <summary>
		/// Particle Cable Constructor
		/// </summary>
		/// <param name="maxLength">The maximal length of the cable in [m].</param>
		/// <param name="restitution">The restitution coefficient of generated contacts [unitless quantity].</param>
		explicit ParticleCable(const float& maxLength = 1.0f, const float& restitution = 0.0f);
		~ParticleCable();

		/// <summary>
		/// Generates new Contacts.
		/// </summary>
		/// <param name="contactData">Out parameter in which new contacts are added.</param>
		void addContact(FixedSizeContainer<ParticleContact>& contactData) const override;

		/// <summary>
		/// Sets the threshold at which contacts will be generated.
		/// </summary>
		/// <param name="maxLength">The maximal length of the cablein [m].</param>
		void setMaxLength(const float& maxLength);

		/// <summary>
		/// Sets the restitution of the generated contacts.
		/// </summary>
		/// <param name="restitution">Restitution coefficient [unitless quantity].</param>
		void setRestitution(const float& restitution);

	protected:
		float m_maxLength;
		float m_restitution;
    };

}