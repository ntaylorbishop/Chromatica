#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Game/Entity.hpp"

const int ENEMY_FIREHOUND_SCORE = 127;
const int ENEMY_FIREHOUND_HEALTH = 3;
const float ENEMY_FIREHOUND_FIRE_RATE = 0.5f;
const float ENEMY_FIREHOUND_MOVESPEED = 0.3f;
const float ENEMY_FIREHOUND_BULLETSPEED = 2.f;
const float ENEMY_FIREHOUND_NUMBULLETSFIRED = 10;
const float ENEMY_FIREHOUND_PHYSRADIUS = 1.0f;

class Firehound : public Entity {
public:
	static Firehound* CreateFirehound();

	//UPDATE
	void Update(float deltaSeconds);
	VIRTUAL void Kill(bool playDeathEffect = true);
	virtual void ApplyDamage(int damageDealt, eOwner bulletOwner);

	//TYPE DEFS
	virtual bool IsEnemy() const { return true; }
	VIRTUAL int GetScoreGivenAmount() const { return ENEMY_FIREHOUND_SCORE; }

private:
	//STRUCTORS
	Firehound();
	void Fire();

	float m_age;
	Vector2 m_dest;
	Vector2 m_velocity;
};