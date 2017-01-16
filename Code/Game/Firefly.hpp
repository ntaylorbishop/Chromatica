#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Game/Entity.hpp"

const int ENEMY_FIREFLY_SCORE = 100;
const int ENEMY_FIREFLY_HEALTH = 2;
const float ENEMY_FIREFLY_FIRE_RATE = 3.f;
const float ENEMY_FIREFLY_MOVESPEED = 1.f;
const float ENEMY_FIREFLY_BULLETSPEED = 2.f;
const float ENEMY_FIREFLY_NUMBULLETSFIRED = 10;
const float ENEMY_FIREFLY_PHYSRADIUS = 0.7f;

class Firefly : public Entity {
public:
	static Firefly* CreateFirefly();

	//UPDATE
	void Update(float deltaSeconds);
	VIRTUAL void Kill(bool playDeathEffect = true);
	virtual void ApplyDamage(int damageDealt, eOwner bulletOwner);

	//TYPE DEFS
	virtual bool IsEnemy() const { return true; }
	VIRTUAL int GetScoreGivenAmount() const { return ENEMY_FIREFLY_SCORE; }

private:
	//STRUCTORS
	Firefly();
	void Fire();

	float m_age;
	Vector2 m_dest;
	Vector2 m_velocity;
};