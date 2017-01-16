#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Game/Entity.hpp"

const int ENEMY_NIGHTMAREBOSS_SCORE = 1234;
const int ENEMY_NIGHTMAREBOSS_HEALTH = 100;
const float ENEMY_NIGHTMAREBOSS_FIRE_RATE = 1.f;
const float ENEMY_NIGHTMAREBOSS_MOVESPEED = 0.1f;
const float ENEMY_NIGHTMAREBOSS_BULLETSPEED = 2.f;
const float ENEMY_NIGHTMAREBOSS_NUMBULLETSFIRED = 10;
const float ENEMY_NIGHTMAREBOSS_PHYSRADIUS = 2.f;

class NightmareBoss : public Entity {
public:
	static NightmareBoss* CreateNightmareBoss();

	//UPDATE
	void Update(float deltaSeconds);
	VIRTUAL void Kill(bool playDeathEffect = true);
	virtual void ApplyDamage(int damageDealt, eOwner bulletOwner);

	//TYPE DEFS
	virtual bool IsEnemy() const { return true; }
	VIRTUAL int GetScoreGivenAmount() const { return ENEMY_NIGHTMAREBOSS_SCORE; }

private:
	//STRUCTORS
	NightmareBoss();
	~NightmareBoss();
	void Fire();

	float m_age;
	Vector2 m_dest;
	Vector2 m_velocity;
};