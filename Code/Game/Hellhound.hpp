#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Game/Entity.hpp"

const int ENEMY_HELLHOUND_SCORE = 186;
const int ENEMY_HELLHOUND_HEALTH = 3;
const float ENEMY_HELLHOUND_FIRE_RATE = 2.f;
const float ENEMY_HELLHOUND_MOVESPEED = 1.f;
const float ENEMY_HELLHOUND_BULLETSPEED = 2.f;
const float ENEMY_HELLHOUND_NUMBULLETSFIRED = 10;
const float ENEMY_HELLHOUND_PHYSRADIUS = 1.6f;

class Hellhound : public Entity {
public:
	static Hellhound* CreateHellhound();

	//UPDATE
	void Update(float deltaSeconds);
	VIRTUAL void Kill(bool playDeathEffect = true);
	virtual void ApplyDamage(int damageDealt, eOwner bulletOwner);

	//TYPE DEFS
	virtual bool IsEnemy() const { return true; }
	VIRTUAL int GetScoreGivenAmount() const { return ENEMY_HELLHOUND_SCORE; }

private:
	//STRUCTORS
	Hellhound();
	void Fire();

	float m_age;
	Vector2 m_dest;
	Vector2 m_velocity;
};