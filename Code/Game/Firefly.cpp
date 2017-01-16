#include "Game/Firefly.hpp"
#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"

STATIC Firefly* Firefly::CreateFirefly() {
	Firefly* nFirefly = new Firefly();
	TheGame::RegisterEnemy(nFirefly);
	return nFirefly;
}

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Firefly::Firefly()
	: m_age(0.f)
{
	AABB2 bounds = TheSpriteRenderer::GetRect();

	m_position = Vector2(Randf(bounds.mins.x + 0.3f, bounds.maxs.x - 0.3f), bounds.maxs.y + 2.f);
	m_dest = Vector2(m_position.x, Randf(bounds.mins.y + 2.f, bounds.maxs.y - 2.f));
	m_velocity = (m_dest - m_position) * ENEMY_FIREFLY_MOVESPEED;

	Initialize(m_position, 0.f, "Firefly", "Foreground");
	m_sprite->m_scale = Vector2(0.4f, 0.4f);
	m_physicsRadius = ENEMY_FIREFLY_PHYSRADIUS;
	m_health = ENEMY_FIREFLY_HEALTH;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void Firefly::Update(float deltaSeconds) {
	m_position = m_position + m_velocity * deltaSeconds;

	if ((m_position - m_dest).Length() <= 0.05f) {
		m_velocity = Vector2::ZERO;
	}


	if (m_position.y <= -6.f) {
		m_isAlive = false;
		TheGame::UnregisterEnemy(this);
	}

	m_age += deltaSeconds;

	if (m_age >= ENEMY_FIREFLY_FIRE_RATE) {
		m_age = 0.f;
		Fire();
	}

	Entity::Update(deltaSeconds);
}

void Firefly::Fire() {
	Projectile::CreateProjectile(m_position, Vector2(0.f, -ENEMY_FIREFLY_BULLETSPEED), "PlayerProjectile", OWNER_AI);
/*
	float angleStep = 360.f / (float)ENEMY_FIREFLY_NUMBULLETSFIRED;

	for (float angle = 0.f; angle < 360.f; angle += angleStep) {
		float xVel = CosDegrees(angle);
		float yVel = SinDegrees(angle);

		Vector2 fireVel = Vector2(xVel, yVel) * ENEMY_FIREFLY_BULLETSPEED;

		Projectile::CreateProjectile(m_position, fireVel, "PlayerProjectile", OWNER_AI);
	}*/
	AudioSystem::PlayFire();
}

VIRTUAL void Firefly::Kill(bool playDeathEffect) {
	m_isAlive = false;
	TheGame::UnregisterEnemy(this);

	if (playDeathEffect) {
		SpawnDeathExplosion();
	}
}
VIRTUAL void Firefly::ApplyDamage(int damageDealt, eOwner bulletOwner) {
	m_health -= damageDealt;

	if (m_health <= 0) {
		m_isAlive = false;
		Kill();

		switch (bulletOwner) {
		case OWNER_AI:
			LogPrintf("AI ship should never die by AI bullet", "ScoreSystem", LOG_DEFAULT);
			break;
		case OWNER_P1:
			g_theGame->m_player1Ship->m_score += GetScoreGivenAmount();
			break;
		case OWNER_P2:
			g_theGame->m_player2Ship->m_score += GetScoreGivenAmount();
			break;
		case OWNER_P3:
			g_theGame->m_player3Ship->m_score += GetScoreGivenAmount();
			break;
		case OWNER_P4:
			g_theGame->m_player4Ship->m_score += GetScoreGivenAmount();
			break;
		default:
			break;
		}
	}
}