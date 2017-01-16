#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Game/Entity.hpp"

const int   ENEMY_PLAGUEBRINGER_SCORE = 100;
const int   ENEMY_PLAGUEBRINGER_HEALTH = 6;
const float ENEMY_PLAGUEBRINGER_FIRE_RATE = 0.8f;
const float ENEMY_PLAGUEBRINGER_MOVESPEED = 1.f;
const float ENEMY_PLAGUEBRINGER_BULLETSPEED = 2.f;
const float ENEMY_PLAGUEBRINGER_SPEED = 1.f;
const float ENEMY_PLAGUEBRINGER_NUMBULLETSFIRED = 10;
const float ENEMY_PLAGUEBRINGER_PHYSRADIUS = 0.7f;

class Plaguebringer : public Entity {
public:
	static Plaguebringer* CreatePlaguebringer();

	//UPDATE
	void Update(float deltaSeconds);
	VIRTUAL void Kill(bool playDeathEffect = true);
	virtual void ApplyDamage(int damageDealt, eOwner bulletOwner);

	//TYPE DEFS
	virtual bool IsEnemy() const { return true; }
	VIRTUAL int GetScoreGivenAmount() const { return ENEMY_PLAGUEBRINGER_SCORE; }

private:
	//STRUCTORS
	Plaguebringer();
	void Fire();

	float m_age;
	Vector2 m_dest;
	Vector2 m_velocity;
	float m_moveAge;
};