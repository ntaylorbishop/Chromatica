#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/EntitySystem/EntitySystem.hpp"
#include "Engine/Renderer/SpriteRenderer/Sprite.hpp"

enum eOwner {
	OWNER_AI = 0,
	OWNER_P1,
	OWNER_P2,
	OWNER_P3,
	OWNER_P4
};

class Entity : public ApparatusEntity {
public:
	Entity();
	virtual ~Entity();

	virtual void Initialize(const Vector2& pos, float rotation, const String& spriteName, const String& layerName);
	virtual void Update(float deltaSeconds);

	void SetPosition(const Vector2& pos);
	virtual void ApplyDamage(int damageDealt);
	virtual void ApplyDamage(int damageDealt, eOwner bulletOwner) { UNREFERENCED_PARAMETER(bulletOwner); UNREFERENCED_PARAMETER(damageDealt); }

	virtual void Kill(bool playDeathEffect = true) = 0;
	virtual void SpawnDeathExplosion();
	
	//TYPE DEFS
	virtual bool IsEnemy() const { return false; }
	virtual bool IsPlayer() const { return false; }
	virtual bool IsProjectile() const { return false; }
	virtual bool IsParticle() const { return false; }
	virtual int GetScoreGivenAmount() const { return 0; }

	Vector2 m_position;
	float m_rotation;
	float m_physicsRadius;
	Sprite* m_sprite;

protected:
	int m_health;
};