#include "ParticlePlaneContact.h"
#include "ParticleContact.h"
#include "Particle.h"

namespace Todes
{
	ParticlePlaneContact::ParticlePlaneContact(float restitution, float radius)
		: m_restitution(restitution)
		, m_radius(radius)
	{
	}

	ParticlePlaneContact::~ParticlePlaneContact()
	{
	}

	void ParticlePlaneContact::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		assert(m_particle && m_plane);

		// Calculate the distance between particle and plane
		const auto& position = m_particle->getPosition();
		auto normal = m_plane->getNormal();

		const auto centerDistance = normal * position - m_plane->getOffset();

		// Distance greater than radius?
		if (centerDistance > m_radius)
			return;

		// Check on which side of the plane the particle is.
		auto penetration = -centerDistance;
		if (centerDistance < 0)
		{
			normal *= -1;
			penetration *= -1;
		}
		penetration += m_radius;

		// Get an available contact and initialize it
		auto contact = contactData.getAvailableEntry();
		contact->Init(m_particle, nullptr, normal);
		contact->setPenetration(penetration);
		contact->setRestitution(m_restitution);
	}

	void ParticlePlaneContact::setRestitution(float restitution)
	{
		m_restitution = restitution;
	}

	void ParticlePlaneContact::setPlane(CollisionPlane* plane)
	{
		m_plane = plane;
	}

	void ParticlePlaneContact::setParticle(Particle* particle)
	{
		m_particle = particle;
	}
}
