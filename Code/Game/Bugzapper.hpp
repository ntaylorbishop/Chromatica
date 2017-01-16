#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Game/Entity.hpp"

const int   ENEMY_BUGZAPPER_SCORE = 100;
const int   ENEMY_BUGZAPPER_HEALTH = 6;
const float ENEMY_BUGZAPPER_FIRE_RATE = 3.f;
const float ENEMY_BUGZAPPER_MOVESPEED = 1.f;
const float ENEMY_BUGZAPPER_BULLETSPEED = 2.f;
const float ENEMY_BUGZAPPER_NUMBULLETSFIRED = 10;
const float ENEMY_BUGZAPPER_PHYSRADIUS = 0.7f;

class Bugzapper : public Entity {
public:
	static Bugzapper* CreateBugzapper();

	//UPDATE
	void Update(float deltaSeconds);
	VIRTUAL void Kill(bool playDeathEffect = true);
	virtual void ApplyDamage(int damageDealt, eOwner bulletOwner);

	//TYPE DEFS
	virtual bool IsEnemy() const { return true; }
	VIRTUAL int GetScoreGivenAmount() const { return ENEMY_BUGZAPPER_SCORE; }

private:
	//STRUCTORS
	Bugzapper();
	void Fire();

	float m_age;
	Vector2 m_dest;
	Vector2 m_velocity;
};