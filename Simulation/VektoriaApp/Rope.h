#pragma once
#include "PlacementParticle.h"

namespace Todes
{
	class Particle;
	class ParticleCable;
	class IParticleContactGenerator;
}

class Rope : public PlacementParticle
{
#pragma region Constructor & Destructor
public:
	explicit Rope
		( Vektoria::CPlacement* placement
		, Vektoria::CGeo* geo
		, Vektoria::CMaterial* material
		, Todes::Particle* particle);

	explicit Rope
		( Vektoria::CPlacement* placement
		, Todes::Particle* particle);

	explicit Rope
		( Vektoria::CPlacement* placement
		, Vektoria::CGeo* geo
		, Vektoria::CMaterial* material
		, const float& particleDamping
		, const float& inverseParticleMass);

	explicit Rope
		( Vektoria::CPlacement* placement
		, const float& particleDamping
		, const float& inverseParticleMass);

	~Rope();
#pragma endregion

#pragma region Init
public:
	void Init
		( Vektoria::CPlacement* anchorPlacement
		, const float& ropeLength
		, const float& ropeRadius = 0.1f
		, const float& restitution = 0.3f);

	void Init
		( Vektoria::CPlacement* anchorPlacement
		, const Vektoria::CMaterial& ropeMaterial
		, const float& ropeLength
		, const float& ropeRadius = 0.1f
		, const float& restitution = 0.3f);
#pragma endregion

public:
	/// <summary>
	/// Returns the Contact Generator underlying the Rope
	/// </summary>
	Todes::IParticleContactGenerator* getContactGenerator();

public:
	/// <summary>
	/// Updates the Rope connection between the anchor and the particle
	/// </summary>
	void update() override;

protected:
	void InitContact
		( const float& ropeLength
		, const float& restitution);
	void InitRope(const float& ropeRadius, const float& ropeLength);

private:
	Todes::ParticleCable* m_ropeContact;
	Vektoria::CGeoCylinder m_ropeGeo;
	Vektoria::CPlacement m_ropePlacement;
	Vektoria::CMaterial m_ropeMaterial;
	Vektoria::CPlacement* m_anchorPlacement;
};

