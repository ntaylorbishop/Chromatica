#include "Game/Plaguebringer.hpp"
#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"

STATIC Plaguebringer* Plaguebringer::CreatePlaguebringer() {
	Plaguebringer* nPlaguebringer = new Plaguebringer();
	TheGame::RegisterEnemy(nPlaguebringer);
	return nPlaguebringer;
}

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Plaguebringer::Plaguebringer()
	: m_age(0.f)
	, m_moveAge(0.f)
{
	AABB2 bounds = TheSpriteRenderer::GetRect();

	m_position = Vector2(0.f, bounds.maxs.y + 2.f);
	m_velocity = Vector2(0.f, -ENEMY_PLAGUEBRINGER_SPEED);

	Initialize(m_position, 0.f, "Plaguebringer", "Foreground");
	m_sprite->m_scale = Vector2(0.3f, 0.3f);
	m_physicsRadius = ENEMY_PLAGUEBRINGER_PHYSRADIUS;
	m_health = ENEMY_PLAGUEBRINGER_HEALTH;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void Plaguebringer::Update(float deltaSeconds) {
	m_moveAge += deltaSeconds * 1.f;
	m_position = m_position + m_velocity * deltaSeconds;

	m_velocity.x = 10.f * cos(m_moveAge);

	if (m_position.y <= -7.f) {
		m_isAlive = false;
		TheGame::UnregisterEnemy(this);
	}
	

	m_age += deltaSeconds;

	if (m_age >= ENEMY_PLAGUEBRINGER_FIRE_RATE) {
		m_age = 0.f;
		Fire();
	}

	Entity::Update(deltaSeconds);
}

void Plaguebringer::Fire() {

	if (m_position.y <= -2.f)
		return;

	int whichPlayer = RandInt(0, 2);
	PlayerShip* target = g_theGame->m_player1Ship;

	switch (whichPlayer) {
	case 0:
		if(g_theGame->m_player2Ship->m_isEnabled)
			target = g_theGame->m_player2Ship;
		break;
	case 1:
		if (g_theGame->m_player3Ship->m_isEnabled)
			target = g_theGame->m_player3Ship;
		break;
	case 2:
		if (g_theGame->m_player4Ship->m_isEnabled)
			target = g_theGame->m_player4Ship;
		break;
	case 3:
		target = g_theGame->m_player1Ship;
	}

	Vector2 vecToPlayer = target->m_position - m_position;
	vecToPlayer.Normalize();
	Projectile::CreateProjectile(m_position, Vector2(0.f, -1.f) * ENEMY_PLAGUEBRINGER_BULLETSPEED, "PlayerProjectile", OWNER_AI);
	/*
	float angleStep = 360.f / (float)ENEMY_PLAGUEBRINGER_NUMBULLETSFIRED;

	for (float angle = 0.f; angle < 360.f; angle += angleStep) {
	float xVel = CosDegrees(angle);
	float yVel = SinDegrees(angle);

	Vector2 fireVel = Vector2(xVel, yVel) * ENEMY_PLAGUEBRINGER_BULLETSPEED;

	Projectile::CreateProjectile(m_position, fireVel, "PlayerProjectile", OWNER_AI);
	}*/
	AudioSystem::PlayFire();
}

VIRTUAL void Plaguebringer::Kill(bool playDeathEffect) {
	m_isAlive = false;
	TheGame::UnregisterEnemy(this);

	if (playDeathEffect) {
		SpawnDeathExplosion();
	}
}
VIRTUAL void Plaguebringer::ApplyDamage(int damageDealt, eOwner bulletOwner) {
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