#pragma once
#include "IParticleForceGenerator.h"

namespace Todes
{
    class Particle;

    /// <summary>
    /// PlanetGravityForce is a force generator, which applies a directed
    /// force towards another particle.
    /// </summary>
    class ParticlePlanetGravityForce : public IParticleForceGenerator
    {
    public:
        /// <summary>
        /// ParticlePlanetGravityForce constructor
        /// </summary>
        /// <param name="centerOfGravity">Particle which is the center of gravity</param>
        /// <param name="gravitationStrength">Strength of the force towards center of gravity</param>
        explicit ParticlePlanetGravityForce(Particle* centerOfGravity, const float& gravitationStrength);
        ~ParticlePlanetGravityForce();

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		void updateForce(Particle* particle) override;

        Particle* getCenterOfGravity();

        void setCenterOfGravity(Particle* newCenter);

        const float& getGravitationStrength() const;

        void setGravitationStrength(const float& newStrength);

        void setInnerRange(const float& innerRange);

        void setOuterRange(const float& outerRange);

    protected:
        Particle* m_centerOfGravity;
        float m_strength;
        float m_innerRange;
        float m_outerRange;
    };

}