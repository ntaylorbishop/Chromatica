#include "Game/Hellhound.hpp"
#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"

STATIC Hellhound* Hellhound::CreateHellhound() {
	Hellhound* nHellhound = new Hellhound();
	TheGame::RegisterEnemy(nHellhound);
	return nHellhound;
}

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Hellhound::Hellhound()
	: m_age(0.f)
{
	AABB2 bounds = TheSpriteRenderer::GetRect();

	m_position = Vector2(Randf(bounds.mins.x + 1.f, bounds.maxs.x - 1.f), bounds.maxs.y + 2.f);
	m_dest = m_position + Vector2(Randf(bounds.mins.x + 1.f, bounds.maxs.x - 1.f), Randf(bounds.mins.y + 2.f, bounds.maxs.y - 2.f));
	m_velocity = (m_dest - m_position) * ENEMY_HELLHOUND_MOVESPEED;

	Initialize(m_position, 0.f, "Hellhound", "Foreground");
	m_physicsRadius = ENEMY_HELLHOUND_PHYSRADIUS;
	m_health = ENEMY_HELLHOUND_HEALTH;
	m_sprite->m_scale = Vector2(0.5f, 0.5f);
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void Hellhound::Update(float deltaSeconds) {
	m_position = m_position + m_velocity * deltaSeconds;

	m_age += deltaSeconds;

	if (m_age >= ENEMY_HELLHOUND_FIRE_RATE) {
		m_age = 0.f;
		Fire();
	}

	if (m_position.y <= -6.f) {
		Kill();
	}

	Entity::Update(deltaSeconds);
}

void Hellhound::Fire() {
	float angleStep = 360.f / (float)ENEMY_HELLHOUND_NUMBULLETSFIRED;
	Projectile::CreateProjectile(m_position, Vector2(0.f, -1.f) * ENEMY_HELLHOUND_BULLETSPEED, "PlayerProjectile", OWNER_AI);

	for (float angle = 0.f; angle < 360.f; angle += angleStep) {
		float xVel = CosDegrees(angle);
		float yVel = SinDegrees(angle);

		Vector2 fireVel = Vector2(xVel, yVel) * ENEMY_HELLHOUND_BULLETSPEED;

	}
	AudioSystem::PlayFire();
}

VIRTUAL void Hellhound::Kill(bool playDeathEffect) {
	m_isAlive = false;
	TheGame::UnregisterEnemy(this);

	if (playDeathEffect) {
		SpawnDeathExplosion();
	}
}

VIRTUAL void Hellhound::ApplyDamage(int damageDealt, eOwner bulletOwner) {
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