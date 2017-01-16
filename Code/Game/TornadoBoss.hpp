#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Game/Entity.hpp"

const int ENEMY_TORNADOBOSS_SCORE = 2345;
const int ENEMY_TORNADOBOSS_HEALTH = 600;
const float ENEMY_TORNADOBOSS_FIRE_RATE = 0.3f;
const float ENEMY_TORNADOBOSS_MOVESPEED = 0.1f;
const float ENEMY_TORNADOBOSS_BULLETSPEED = 2.f;
const float ENEMY_TORNADOBOSS_NUMBULLETSFIRED = 10;
const float ENEMY_TORNADOBOSS_PHYSRADIUS = 3.f;
const float ENEMY_TORNADOBOSS_FIRETIME = 0.3f;

class TornadoBoss : public Entity {
public:
	static TornadoBoss* CreateTornadoBoss();

	//UPDATE
	void Update(float deltaSeconds);
	VIRTUAL void Kill(bool playDeathEffect = true);
	virtual void ApplyDamage(int damageDealt, eOwner bulletOwner);

	//TYPE DEFS
	virtual bool IsEnemy() const { return true; }
	VIRTUAL int GetScoreGivenAmount() const { return ENEMY_TORNADOBOSS_SCORE; }

private:
	//STRUCTORS
	TornadoBoss();
	~TornadoBoss();
	void Fire(float deltaSeconds);

	float m_camAge;
	float m_fireAge;
	float m_age;
	float m_currAngle;
	float m_currAngleStep;
	Vector2 m_dest;
	Vector2 m_velocity;
};