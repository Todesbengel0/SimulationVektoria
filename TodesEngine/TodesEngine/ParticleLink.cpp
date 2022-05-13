#include "ParticleLink.h"
#include "Particle.h"
#include "ParticleContact.h"

namespace Todes
{
	ParticleLink::ParticleLink(const float& triggerDistance /*= 1.0f*/, const float& restitution /*= 0.0f*/)
		: m_triggerDistance(triggerDistance), m_restitution(restitution)
	{ }

	ParticleLink::~ParticleLink()
		= default;

	void ParticleLink::setParticles(Particle* first, Particle* second)
	{
		m_particles[0] = first;
		m_particles[1] = second;
	}

	void ParticleLink::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		const auto penetration = calculatePenetration();
		if (penetration <= 0.0f) return;
		
		// Get an unused contact
		auto contact = contactData.getAvailableEntry();

		assert(contact);

		contact->Init(m_particles[0], m_particles[1]);
		contact->setContactNormal(calculateContactNormal());
		contact->setPenetration(penetration);
		contact->setRestitution(m_restitution);
	}

	Particle* ParticleLink::getFirst() const
	{
		return m_particles[0];
	}

	Particle* ParticleLink::getSecond() const
	{
		return m_particles[1];
	}

	void ParticleLink::setRestitution(const float& restitution)
	{
		m_restitution = restitution;
	}

	void ParticleLink::setTriggerDistance(const float& distance)
	{
		m_triggerDistance = distance;
	}

	float ParticleLink::currentLength() const
	{
		assert(m_particles[0] && m_particles[1]);

		const auto distance = m_particles[0]->getPosition() - m_particles[1]->getPosition();
		return distance.Length();
	}

	Vector3D ParticleLink::calculateContactNormal() const
	{
		// Contact normal n = (a.position - b.positon).Norm
		auto normal = m_particles[0]->getPosition() - m_particles[1]->getPosition();
		return normal.Normalize();
	}
}