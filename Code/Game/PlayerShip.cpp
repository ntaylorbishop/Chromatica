#include "Game/PlayerShip.hpp"
#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"
#include "Game/GameParticle.hpp"

STATIC PlayerShip* PlayerShip::CreatePlayerShip(uint controllerID, RGBA tint) {
	PlayerShip* nPlayerShip = new PlayerShip(controllerID, tint);
	return nPlayerShip;
}

//STRUCTORS
PlayerShip::PlayerShip(uint controllerID, RGBA tint)
	: m_fireAge(0.f)
	, m_playerFireStage(0)
	, m_fireRate(PLAYER_FIRE_RATE)
	, m_isEnabled(false)
	, m_remainingLives(3)
	, m_ownerType(OWNER_P1)
	, m_score(0)
	, m_deathAge(0.f)
	, m_hasDied(false)
{ 
	switch (controllerID) {
	case 0:
		Initialize(PLAYER_START_POSITION, 0.f, "Player1", "Foreground");
		m_sprite->m_scale = Vector2(0.2f, 0.2f);
		break;
	case 1:
		Initialize(PLAYER_START_POSITION, 0.f, "Player2", "Foreground");
		m_sprite->m_scale = Vector2(0.3f, 0.3f);
		m_sprite->m_rotation = 180.f;
		m_ownerType = OWNER_P2;
		break;
	case 2:
		Initialize(PLAYER_START_POSITION, 0.f, "Player3", "Foreground");
		m_sprite->m_scale = Vector2(0.3f, 0.3f);
		m_sprite->m_rotation = 180.f;
		m_ownerType = OWNER_P3;
		break;
	case 3:
		Initialize(PLAYER_START_POSITION, 0.f, "Player4", "Foreground");
		m_sprite->m_scale = Vector2(0.3f, 0.3f);
		m_sprite->m_rotation = 180.f;
		m_ownerType = OWNER_P4;
		break;
	}
	m_sprite->m_tint = tint;
	m_physicsRadius = PLAYER_PHYSRADIUS;
	m_health = PLAYER_HEALTH;
	m_sprite->Enable();

	m_controller = XboxController(controllerID);

	if (!m_controller.IsConnected()) {
		m_sprite->Disable();
	}

	if (controllerID == 0) {
		m_isEnabled = true;
		m_sprite->Enable();
	}
}
PlayerShip::~PlayerShip() { }

//UPDATE
void PlayerShip::Update(float deltaSeconds) {

	m_controller.Update();

	if (m_hasDied) {
		PlayDeathSequence(deltaSeconds);

		if (m_deathAge >= PLAYER_RESPAWN_RATE) {
			if (m_controller.GetControllerID() == 0 && m_remainingLives > 0) {
				if (g_theInputSystem->GetKeyDown(VK_RETURN) || m_controller.GetButtonDown(XB_START)) {
					m_hasDied = false;
					m_sprite->m_tint = RGBA::WHITE;
					m_deathAge = 0.f;
					m_health = PLAYER_HEALTH;
				}
			}
			else if (m_controller.GetControllerID() != 0 && m_remainingLives > 0) {
				if (m_controller.GetButtonDown(XB_START)) {
					m_hasDied = false;
					m_sprite->m_tint = RGBA::WHITE;
					m_deathAge = 0.f;
					m_health = PLAYER_HEALTH;
				}
			}
		}
	}

	if (m_controller.GetControllerID() == 0 && !m_hasDied) {
		m_fireAge += deltaSeconds;
		HandleInput(deltaSeconds);
	}
	else if(m_controller.GetControllerID() != 0) {
		if (m_controller.IsConnected() && !m_hasDied) {
			EnablePlayer();
			m_fireAge += deltaSeconds;
			m_controller.Update();

			HandleInput(deltaSeconds);
		}
		else if(!m_controller.IsConnected()) {
			DisablePlayer();
		}
	}
}

void PlayerShip::EnablePlayer() {
	if (!m_isEnabled) {
		m_sprite->Enable();
		m_isEnabled = true;
		//g_theGame->m_playerCount++;
	}
}
void PlayerShip::DisablePlayer() {
	if (m_isEnabled) {
		m_sprite->Disable();
		m_isEnabled = false;
		//g_theGame->m_playerCount--;
	}
}

void PlayerShip::Upgrade() {
	m_playerFireStage++;
	m_fireRate -= 0.2f;
}

//INPUT
void PlayerShip::HandleInput(float deltaSeconds) {

	////////////////////////////////////////////////////
	//------------------------------------------
/*
	PolarCoords leftStickPolar = m_controller.GetLeftStickPositionPolar();
	Vector2 xyMovement = leftStickPolar.ToVector2_InRadians();*/

	//CONTROLLER
	float dir = 0.f;
	if (m_controller.GetLeftStickPosition().x < 0.f)
		dir = -1.f;
	else if (m_controller.GetLeftStickPosition().x > 0.f)
		dir = 1.f;




	SetPosition(m_position + Vector2(dir * PLAYER_SPEED * deltaSeconds, 0.f));

	if (m_controller.GetRightTriggerValue() > 0.f) {
		if (m_fireAge >= PLAYER_FIRE_RATE) {
			m_fireAge = 0.f;
			Fire(deltaSeconds);
		}
	}

	/////////////////////////////////////////////////////
	//------------------------------------------
	//KEYBOARD
	if (m_controller.GetControllerID() != 0)
		return;

	if (g_theInputSystem->GetKey('A') || g_theInputSystem->GetKey(VK_LEFT)) {
		float speed = PLAYER_SPEED * deltaSeconds;
		SetPosition(m_position + Vector2(-speed, 0.f));
	}
	else if (g_theInputSystem->GetKey('D') || g_theInputSystem->GetKey(VK_RIGHT)) {
		float speed = PLAYER_SPEED * deltaSeconds;
		SetPosition(m_position + Vector2(speed, 0.f));
	}

	if (g_theInputSystem->GetKey(VK_SPACE)) {
		if (m_fireAge >= PLAYER_FIRE_RATE) {
			m_fireAge = 0.f;
			Fire(deltaSeconds);
		}
	}
}
void PlayerShip::Fire(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);
	switch (m_playerFireStage) {
	case 0:
		AudioSystem::PlayFire();
		Projectile::CreateProjectile(m_position, Vector2(0.f, PLAYER_PROJECTILE_SPEED), "PlayerProjectile", m_ownerType);
		break;
	case 1:
		AudioSystem::PlayFire();
		Projectile::CreateProjectile(m_position, Vector2(CosDegrees(70.f), SinDegrees(70.f)) *  PLAYER_PROJECTILE_SPEED, "PlayerProjectile", m_ownerType);
		Projectile::CreateProjectile(m_position, Vector2(CosDegrees(90.f), SinDegrees(90.f)) *  PLAYER_PROJECTILE_SPEED, "PlayerProjectile", m_ownerType);
		Projectile::CreateProjectile(m_position, Vector2(CosDegrees(110.f), SinDegrees(110.f)) *  PLAYER_PROJECTILE_SPEED, "PlayerProjectile", m_ownerType);
		break;
	case 2:
		AudioSystem::PlayFire();
		//Projectile::CreateProjectile(m_position, Vector2(CosDegrees(70.f), SinDegrees(70.f)) *  PLAYER_PROJECTILE_SPEED, "PlayerProjectile", m_ownerType);
		Projectile::CreateProjectile(m_position, Vector2(CosDegrees(80.f), SinDegrees(80.f)) *  PLAYER_PROJECTILE_SPEED, "PlayerProjectile", m_ownerType);
		Projectile::CreateProjectile(m_position, Vector2(CosDegrees(90.f), SinDegrees(90.f)) *  PLAYER_PROJECTILE_SPEED, "PlayerProjectile", m_ownerType);
		Projectile::CreateProjectile(m_position, Vector2(CosDegrees(100.f), SinDegrees(100.f)) *  PLAYER_PROJECTILE_SPEED, "PlayerProjectile", m_ownerType);
		//Projectile::CreateProjectile(m_position, Vector2(CosDegrees(110.f), SinDegrees(110.f)) *  PLAYER_PROJECTILE_SPEED, "PlayerProjectile", m_ownerType);
		break;
	}
}

VIRTUAL void PlayerShip::ApplyDamage(int damageDealt) {
	m_health -= damageDealt;

	if (m_health <= 0) {
		Kill();
		SpawnSuperMegaDeathExplosion();
	}
}
VIRTUAL void PlayerShip::Kill(bool playDeathEffect) {
	m_remainingLives--;
	SpawnDeathExplosion();
	m_hasDied = true;
}

void PlayerShip::PlayDeathSequence(float deltaSeconds) {
	m_deathAge += deltaSeconds;
	
	float deathOpacity = RangeMap(m_deathAge, 0.f, PLAYER_RESPAWN_RATE, 1.f, 0.f);
	m_sprite->m_tint = RGBA(1.f, 1.f, 1.f, deathOpacity);
}
void PlayerShip::SpawnSuperMegaDeathExplosion() {
	for (uint i = 0; i < 100; i++) {
		float velScale = Randf(3.f, 10.f);
		Vector2 vel = Vector2(Randf(-1.f, 1.f) * velScale, Randf(-1.f, 1.f) * velScale);
		GameParticle* nParticle = new GameParticle(m_position, vel, "PlayerProjectile");
		nParticle->m_sprite->m_scale = Vector2(0.01f, 0.01f);
		nParticle->m_isFading = true;
	}
}

void PlayerShip::Refresh() {
	m_position = PLAYER_START_POSITION;
	m_rotation = 0;
	m_health = PLAYER_HEALTH;
	m_isEnabled = false;
	m_score = 0;
	m_remainingLives = 3;
	m_hasDied = false;
	m_deathAge = 0.f;
	m_fireRate = 0.f;
	m_playerFireStage = 0;
	m_fireAge = 0.f;
}