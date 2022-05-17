#pragma once

namespace Todes
{
	class Particle;
}

class PlacementParticle
{
public:
	explicit PlacementParticle(Vektoria::CPlacement* placement,
								Vektoria::CGeo* geo,
								Vektoria::CMaterial* material,
								Todes::Particle* particle);
	explicit PlacementParticle(Vektoria::CPlacement* placement,
								Todes::Particle* particle);
	explicit PlacementParticle(Vektoria::CPlacement* placement,
								Vektoria::CGeo* geo,
								Vektoria::CMaterial* material,
								const float& particleDamping,
								const float& inverseParticleMass);
	explicit PlacementParticle(Vektoria::CPlacement* placement,
								const float& particleDamping,
								const float& inverseParticleMass);

	explicit PlacementParticle();
	~PlacementParticle();

public:
	/** Update the scene graph node with the associated particle node. */
	virtual void update();
	virtual void update(const float& timeDelta);

	// Resets the Placement Particle to the start condition
	virtual void reset();

	// Kills the Placement Particle
	virtual void kill();

	// Destroys this Placement Particle
	virtual void destroy();

	// Revives Placement Particles
	virtual void revive() const;

	bool isDirty() const;

public:
	/** Set the current particle. */
	void setParticle(Todes::Particle* particle);
	/** Get the current particle. */
	Todes::Particle* getParticle() const;

	/** Set the current placement. */
	void setPlacement(Vektoria::CPlacement* placement);
	/** Get the current placement. */
	Vektoria::CPlacement* getPlacement() const;

	/** Set the current geo. */
	void setGeo(Vektoria::CGeo* geo);
	/** Get the current geo. */
	Vektoria::CGeo* getGeo() const;

	/** Set the current material. */
	void setMaterial(Vektoria::CMaterial* material);
	/** Get the current material. */
	Vektoria::CMaterial* getMaterial() const;

protected:
	Vektoria::CPlacement* m_placement;
	Vektoria::CGeo* m_geo;
	Vektoria::CMaterial* m_material;
	Todes::Particle* m_particle;
	bool m_dirty;
};

