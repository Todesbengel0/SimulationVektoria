#pragma once
#include "IParticleForceGenerator.h"
#include "Vector3D.h"
#include <vector>
#include <initializer_list>
constexpr auto QUATERPI = 0.785398f;

namespace Todes
{
    struct CalmSpace final
    {
        Vector3D calmOrigin;
        Vector3D calmDimensions;

        friend bool operator==(const CalmSpace& lhs, const CalmSpace& rhs)
        {
            return lhs.calmOrigin == rhs.calmOrigin && lhs.calmDimensions == rhs.calmDimensions;
        }
    };

    /// <summary>
    /// Force Generator for wind working on a particle
    /// </summary>
    class ParticleTyphoon : public IParticleForceGenerator
    {
    public:
        /// <summary>
        /// ParticleTyphoon Constructor
        /// </summary>
        /// <param name="particleHalfHeigt">Radius/Half Height of the Particle in [m]</param>
        /// <param name="calmSpaces">Initializer List of calm spaces</param>
        /// <param name="calmOrigin">Origin of wind calm space in [mxmxm]</param>
        /// <param name="calmDimensions">Dimensions of wind calm space in [mxmxm]</param>
        /// <param name="minStrength">Minimum Strength of the Typhoon in [m/s]</param>
        /// <param name="maxStrength">Maximum Strangth of the Typhoon in [m/s]</param>
        /// <param name="maxDifference">Maximum Angular Difference in wind direction per update in [RAD]</param>
        /// <param name="chaosChance">Chance for the wind direction to change completely in [%]</param>
        /// <param name="calmResistance">Resistance in [%] (without restraints) that wind calm spaces apply.</param>
        explicit ParticleTyphoon
        (
            const float& particleHalfHeight,
            const std::initializer_list<CalmSpace>& calmSpaces,
            const float& minStrength,
            const float& maxStrength,
            const float& maxDifference = QUATERPI,
            const float& chaosChance = 0.0f,
            const float& calmResistance = 0.0f
        );
        ~ParticleTyphoon();

		/// <summary>
		/// Calculates and changes the force in the force accumulator of a particle.
		/// </summary>
		/// <param name="particle">The particle, on which the force should be applied to.</param>
		void updateForce(Particle* particle) override;

        /// <summary>
        /// Returns the Half Height of the Particle
        /// </summary>
        const float& getHalfHeight() const;

        /// <summary>
        /// Returns the Calm Spaces
        /// </summary>
        const std::vector<CalmSpace>& getCalmSpaces() const;

        /// <summary>
        /// Returns the Minimum Strength of the Typhoon
        /// </summary>
        const float& getMinStrength() const;

        /// <summary>
        /// Returns the Maximum Strength of the Typhoon
        /// </summary>
        const float& getMaxStrength() const;

        /// <summary>
        /// Returns the Maximum Angular Difference in wind direction per update
        /// </summary>
        const float& getMaxDifference() const;

        /// <summary>
        /// Returns the Chance for the wind direction to change completely
        /// </summary>
        const float& getChaosChance() const;

        /// <summary>
        /// Returns the Resistance in that wind calm spaces apply.
        /// </summary>
        const float& getCalmResistance() const;

        /// <summary>
        /// Sets the Half Height of the Particle
        /// </summary>
        /// <param name="particleHalfHeight">Radius / Half Height of the Particle in [m]</param>
        void setHalfHeight(const float& particleHalfHeight);

        /// <summary>
        /// Sets the Origin and Dimensions of the wind calm space
        /// </summary>
        /// <param name="whatSpace">Calm Space to change</param>
        /// <param name="toSpace">Calm Space to change into</param>
        /// <return>TRUE: Calm Space was found and changed. FALSE: otherwise</return>
        bool setCalmSpace(const CalmSpace& whatSpace, const CalmSpace& toSpace);

        /// <summary>
        /// Adds a wind calm space
        /// </summary>
        /// <param name="calmSpace">Calm Space to add</param>
        void addCalmSpace(const CalmSpace& calmSpace);

        /// <summary>
        /// Removes a wind calm space
        /// </summary>
        /// <param name="calmSpace">Calm Space to remove</param>
        /// <returns>TRUE: Calm Space was found and removed. FALSE: otherwise</returns>
        bool removeCalmSpace(const CalmSpace& calmSpace);

        /// <summary>
        /// Sets the Strength of the Typhoon
        /// </summary>
        /// <param name="minStrength">Minimum Strength of the Typhoon in [m/s]</param>
        /// <param name="maxStrength">Maximum Strangth of the Typhoon in [m/s]</param>
        void setStrength(const float& minStrength, const float& maxStrength);

        /// <summary>
        /// Sets the Maximum Angular Difference in wind direction per update
        /// </summary>
        /// <param name="maxDifference">Maximum Angular Difference in [RAD]</param>
        void setMaxDifference(const float& maxDifference);

        /// <summary>
        /// Sets the Chance for the wind direction to change completely
        /// </summary>
        /// <param name="chaosChance">Chaos Chance in [%]</param>
        void setChaosChance(const float& chaosChance);

        /// <summary>
        /// Sets the Resistance in that wind calm spaces apply.
        /// </summary>
        /// <param name="calmResistance">Resistance in [%] (without restraints)</param>
        void setCalmResistance(const float& calmResistance);

    protected:
        float m_particleHalfHeight;
        std::vector<CalmSpace> m_calmSpaces;

        float m_minStrength;
        float m_maxStrength;
        float m_maxDifference;
        float m_chaosChance;
        float m_calmResistance;

        Vector3D m_currentDirection;
    };
}

