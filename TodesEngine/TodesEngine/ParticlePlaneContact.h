#pragma once
#include "IParticleContactGenerator.hpp"

namespace Todes
{
	class Particle;
	class CollisionPlane;

    class ParticlePlaneContact : public IParticleContactGenerator
    {
	public:
		ParticlePlaneContact(float restitution, float radius);
		~ParticlePlaneContact();

		void addContact(FixedSizeContainer<ParticleContact>& contactData) const override;

		void setRestitution(float restitution);
		void setPlane(CollisionPlane* plane);
		void setParticle(Particle* particle);

	private:
		float m_restitution;
		Particle* m_particle{};
		float m_radius;
		CollisionPlane* m_plane{};
    };
}
