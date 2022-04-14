#pragma once

class Particle;


class PlacementParticle
{
public:
	explicit PlacementParticle(Vektoria::CPlacement* placement,
								Vektoria::CGeo* geo,
								Vektoria::CMaterial* material,
								Particle* particle);
	explicit PlacementParticle(Vektoria::CPlacement* placement,
								Particle* particle);
	explicit PlacementParticle();
	~PlacementParticle();

public:
	/** Update the scene graph node with the associated particle node. */
	void update() const;

public:
	/** Set the current particle. */
	void setParticle(Particle* particle);
	/** Get the current particle. */
	Particle* getParticle() const;

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

private:
	Vektoria::CPlacement* m_placement;
	Vektoria::CGeo* m_geo;
	Vektoria::CMaterial* m_material;
	Particle* m_particle;
};

