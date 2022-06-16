#pragma once
#include "Scenes/CaveScene.h"
#include "ForceDefines.h"
#include "CTailPlacements.h"

class PlacementParticle;
class PlacementParticleWorld;
class Firework;
namespace Vektoria { class CGeoTail; }

class FireworkScene : public CaveScene
{

public:
	explicit FireworkScene(const bool& changeScene = true, const std::size_t& tailCount = 15000);
	explicit FireworkScene
		( const std::size_t& tailCount = 15000
		, const float& translationZ = 10.0f
		, const float& caveWidth = 30.0f
		, const float& caveDepth = 20.0f
		, const float& caveHeight = 20.0f
		, const float& wallThickness = 0.1f);
	~FireworkScene();

	void update(float timeDelta) override;
	void spawn() override;

	PlacementParticleWorld* getWorld() const;

	void registerFirework(Firework* firework) const;
	void removeFirework(Firework* firework) const;

protected:
	PlacementParticleWorld* m_particleWorld;
	Vektoria::CMaterial* m_fireworkMaterial;
	Vektoria::CGeoSphere* m_fireworkGeo;
	Vektoria::CGeoTail* m_tailGeo;
	Vektoria::CTailPlacements* m_tail;
};

