#include "Game/Bugzapper.hpp"
#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"

STATIC Bugzapper* Bugzapper::CreateBugzapper() {
	Bugzapper* nBugzapper = new Bugzapper();
	TheGame::RegisterEnemy(nBugzapper);
	return nBugzapper;
}

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Bugzapper::Bugzapper()
	: m_age(0.f)
{
	AABB2 bounds = TheSpriteRenderer::GetRect();

	m_position = Vector2(Randf(bounds.mins.x - 1.f, bounds.maxs.x + 1.f), bounds.maxs.y + 2.f);
	m_dest = Vector2(m_position.x, Randf(bounds.mins.y + 2.f, bounds.maxs.y - 2.f));
	m_velocity = (m_dest - m_position) * ENEMY_BUGZAPPER_MOVESPEED;

	Initialize(m_position, 0.f, "Bugzapper", "Foreground");
	m_sprite->m_scale = Vector2(0.4f, 0.4f);
	m_physicsRadius = ENEMY_BUGZAPPER_PHYSRADIUS;
	m_health = ENEMY_BUGZAPPER_HEALTH;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void Bugzapper::Update(float deltaSeconds) {
	m_position = m_position + m_velocity * deltaSeconds;

	if ((m_position - m_dest).Length() <= 0.05f) {
		m_velocity = Vector2::ZERO;
	}

	m_age += deltaSeconds;

	if (m_age >= ENEMY_BUGZAPPER_FIRE_RATE) {
		m_age = 0.f;
		Fire();
	}

	Entity::Update(deltaSeconds);
}

void Bugzapper::Fire() {
	Projectile::CreateProjectile(m_position, Vector2(0.f, -ENEMY_BUGZAPPER_BULLETSPEED), "PlayerProjectile", OWNER_AI);
	
	float angleStep = 360.f / (float)ENEMY_BUGZAPPER_NUMBULLETSFIRED;

	for (float angle = 0.f; angle < 360.f; angle += angleStep) {
	float xVel = CosDegrees(angle);
	float yVel = SinDegrees(angle);

	Vector2 fireVel = Vector2(xVel, yVel) * ENEMY_BUGZAPPER_BULLETSPEED;

	Projectile::CreateProjectile(m_position, fireVel, "PlayerProjectile", OWNER_AI);
	}
	AudioSystem::PlayFire();
}

VIRTUAL void Bugzapper::Kill(bool playDeathEffect) {
	m_isAlive = false;
	TheGame::UnregisterEnemy(this);

	if (playDeathEffect) {
		SpawnDeathExplosion();
	}
}
VIRTUAL void Bugzapper::ApplyDamage(int damageDealt, eOwner bulletOwner) {
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