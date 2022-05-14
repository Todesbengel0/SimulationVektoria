#pragma once
#include "Vector3D.h"

namespace Todes
{
	class Particle;

	/// <summary>
	/// A ParticleContact contains contact information of two particles.
	/// </summary>
	class ParticleContact
	{
	public:
		/// <summary>
		/// ParticleContact Constructor
		/// </summary>
		explicit ParticleContact();

		/// <summary>
		/// ParticleContact Constructor 2
		/// </summary>
		/// <param name="first">First particle of the contact.</param>
		/// <param name="second">Second particle of the contact.</param>
		explicit ParticleContact(Particle* first, Particle* second);
		~ParticleContact();

		/// <summary>
		/// Initializes the contact
		/// </summary>
		/// <param name="first">First particle of the contact.</param>
		/// <param name="second">Second particle of the contact.</param>
		void Init(Particle* first, Particle* second);

		/// <summary>
		/// Calculates and returns the separating velocity.
		/// </summary>
		float CalculateSeparatingVelocity() const;

		/// <summary>
		/// Resolves the velocity and interpenetration
		/// </summary>
		/// <param name="timeDelta">The amount of time that has passed</param>
		/// <returns>Particle Translations through resolving Interpenetration</returns>
		std::pair<Vector3D, Vector3D> resolve(const float& timeDelta);

		/// <summary>
		/// Returns the contact's particles.
		/// </summary>
		Particle* getParticles();

		/// <summary>
		/// Sets the contact's contact normal.
		/// </summary>
		void setContactNormal(const Vector3D& normal);

		/// <summary>
		/// Returns the current contact normal.
		/// </summary>
		const Vector3D& getContactNormal() const;

		/// <summary>
		/// Sets the contact's restitution.
		/// </summary>
		/// <param name="restitution"></param>
		void setRestitution(const float& restitution);

		/// <summary>
		/// Returns the contact's restitution.
		/// </summary>
		const float& getRestitution() const;

		/// <summary>
		/// Sets the contact's penetration.
		/// </summary>
		void setPenetration(const float& penetration);

		/// <summary>
		/// Adds a value to the contact's penetration
		/// </summary>
		/// <param name="summand">Value to add to penetration</param>
		void AddPenetration(const float& summand);

		/// <summary>
		/// Returns the current penetration.
		/// </summary>
		const float& getPenetration() const;

		/// <summary>
		/// Returns the first particle of the contact.
		/// </summary>
		Particle* getFirst() const;

		/// <summary>
		/// Returns the second particle of the contact.
		/// </summary>
		Particle* getSecond() const;

	private:
		/// <summary>
		/// Checks if this Contact is resting. Adjusts particle movements if it is.
		/// </summary>
		/// <returns>TRUE: Contact is resting. FALSE: Contact is forcefull.</returns>
		bool isResting(const float& timeDelta);

		/// <summary>
		/// Resolves the velocity for the particles.
		/// </summary>
		/// <param name="timeDelta">Time step of this update.</param>
		void ResolveVelocity(const float& timeDelta);

		/// <summary>
		/// Resolves the interpenetration of the particles.
		/// </summary>
		/// <param name="timeDelta">Time step of this update.</param>
		/// <returns>Particle Translations through resolving Interpenetration</returns>
		std::pair<Vector3D, Vector3D> ResolveInterpenetration(const float& timeDelta);

	protected:
		Particle* m_particles[2];
		float m_restitution;
		Vector3D m_contactNormal;
		float m_penetration;
	};
}