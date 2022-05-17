#pragma once
#include "PlacementParticle.h"

class CaveScene;

namespace Todes
{
	class Particle;
	class ParticleCable;
	class IParticleContactGenerator;
}

class Pendulum : public PlacementParticle
{
#pragma region Constructor & Destructor
public:
	explicit Pendulum
		( Vektoria::CPlacement* placement
		, Vektoria::CGeo* geo
		, Vektoria::CMaterial* material
		, Todes::Particle* particle);

	explicit Pendulum
		( Vektoria::CPlacement* placement
		, Todes::Particle* particle);

	explicit Pendulum
		( Vektoria::CPlacement* placement
		, Vektoria::CGeo* geo
		, Vektoria::CMaterial* material
		, const float& particleDamping
		, const float& inverseParticleMass);

	explicit Pendulum
		( Vektoria::CPlacement* placement
		, const float& particleDamping
		, const float& inverseParticleMass);

	~Pendulum();
#pragma endregion

#pragma region Init
public:
	void Init
		( CaveScene* scene
		, const Todes::Vector3D& anchorPosition
		, const float& ropeLength
		, const float& ropeRadius = 0.1f
		, const float& restitution = 0.3f);

	void Init
		( CaveScene* scene
		, const Todes::Vector3D& anchorPosition
		, const Vektoria::CMaterial& ropeMaterial
		, const float& ropeLength
		, const float& ropeRadius = 0.1f
		, const float& restitution = 0.3f);

	void Init
		(CaveScene* scene
		, PlacementParticle* anchorPlacementParticle
		, const float& ropeLength
		, const float& ropeRadius = 0.1f
		, const float& restitution = 0.3f);

	void Init
		(CaveScene* scene
		, PlacementParticle* anchorPlacementParticle
		, const Vektoria::CMaterial& ropeMaterial
		, const float& ropeLength
		, const float& ropeRadius = 0.1f
		, const float& restitution = 0.3f);
#pragma endregion

public:
	/// <summary>
	/// Returns the Contact Generator underlying the Pendulum
	/// </summary>
	Todes::IParticleContactGenerator* getContactGenerator();

public:
	/// <summary>
	/// Updates the Pendulum connection between the anchor and the particle
	/// </summary>
	void update() override;

protected:
	void InitMaterial(CaveScene* scene);
	void InitContact
		( const Todes::Vector3D& anchorPosition
		, const float& ropeLength
		, const float& restitution);
	void InitContact
		( Todes::Particle* anchorParticle
		, const float& ropeLength
		, const float& restitution);
	void InitRope(const float& ropeRadius, const float& ropeLength);

private:
	Todes::ParticleCable* m_ropeContact;
	Vektoria::CGeoCylinder m_ropeGeo;
	Vektoria::CPlacement m_ropePlacement;
	Vektoria::CMaterial m_ropeMaterial;
	Vektoria::CPlacement m_pointingPlacement;
	Vektoria::CPlacement* m_anchorPlacement;
};

