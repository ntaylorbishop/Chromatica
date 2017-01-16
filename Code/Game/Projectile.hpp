#pragma once

#include "Engine/Math/Vector2.hpp"
#include "Game/Entity.hpp"

const float PROJECTILE_PHYSRADIUS = 0.06f;

class Projectile : public Entity {
public:

	static Projectile* CreateProjectile(const Vector2& pos, const Vector2& vel, const String& name, eOwner owner);


	void Update(float deltaSeconds);
	VIRTUAL void Kill(bool playDeathEffect = true);

	//TYPE DEFS
	virtual bool IsProjectile() const { return true; }

	eOwner m_owner;
	Vector2 m_velocity;
	bool m_isFading;

private:
	Projectile(const Vector2& pos, const Vector2& vel, const String& name, eOwner owner);

	//INHERITED
	//Vector2 m_position;
	//float m_rotation;
	//Sprite* m_sprite;
};