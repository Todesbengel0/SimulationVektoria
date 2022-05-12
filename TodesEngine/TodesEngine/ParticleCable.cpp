#include "ParticleCable.h"
#include "Particle.h"
#include "ParticleContact.h"

namespace Todes
{
	ParticleCable::ParticleCable(const float& maxLength /*= 1.0f*/, const float& restitution /*= 0.0f*/)
		: m_maxLength(maxLength)
		, m_restitution(restitution)
	{ }

	ParticleCable::~ParticleCable()
		= default;

	void ParticleCable::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		const auto length = currentLength();
		if (length < m_maxLength) return;

		// Get an unused contact
		auto contact = contactData.getAvailableEntry();
		
		assert(contact);

		contact->Init(m_particles[0], m_particles[1]);

		// Negative contact normal
		auto normal = m_particles[1]->getPosition() - m_particles[0]->getPosition();
		normal.Normalize();

		contact->setContactNormal(normal);
		contact->setPenetration(length - m_maxLength);
		contact->setRestitution(m_restitution);
	}

	void ParticleCable::setMaxLength(const float& maxLength)
	{
		m_maxLength = maxLength;
	}

	void ParticleCable::setRestitution(const float& restitution)
	{
		m_restitution = restitution;
	}
}