#pragma once

#include "Engine/General/Input/XboxController.hpp"
#include "Game/Entity.hpp"

const Vector2 PLAYER_START_POSITION = Vector2(0.f, -4.5f);
const float PLAYER_SPEED = 5.f;
const float PLAYER_PHYSRADIUS = .2f;
const int PLAYER_HEALTH = 4;
const int PLAYER_DAMAGE = 1;
const int PLAYER_DAMAGE_TAKEN = 1;
const float PLAYER_PROJECTILE_SPEED = 10.f;
const float PLAYER_FIRE_RATE = 0.2f;
const float PLAYER_RESPAWN_RATE = 3.f;

class PlayerShip : public Entity {
public:
	static PlayerShip* CreatePlayerShip(uint controllerID, RGBA tint);
	//STRUCTORS
	~PlayerShip();

	//UPDATE
	void Update(float deltaSeconds);

	void Refresh();

	void EnablePlayer();
	void DisablePlayer();

	VIRTUAL void ApplyDamage(int damageDealt);
	VIRTUAL void Kill(bool playDeathEffect = true);
	void Upgrade();

	//TYPE DEFS
	virtual bool IsPlayer() const { return true; }
	bool IsDead() const { return (m_remainingLives <= 0 && m_isEnabled); }

	void PlayDeathSequence(float deltaSeconds);
	void SpawnSuperMegaDeathExplosion();

	const String m_fireSound = "Data/Sounds/PlayerFire.wav";
	bool m_isEnabled;
	int m_score;
	XboxController m_controller;
	int m_remainingLives;
	eOwner m_ownerType;
	bool m_hasDied;

private:
	PlayerShip(uint controllerID, RGBA tint);
	//INPUT
	void HandleInput(float deltaSeconds);
	void Fire(float deltaSeconds);

	float m_deathAge;

	float m_fireRate;
	uint m_playerFireStage;
	float m_fireAge;


	//INHERITED
	//Vector2 m_position;
	//float m_rotation;
	//Sprite* m_sprite;

};