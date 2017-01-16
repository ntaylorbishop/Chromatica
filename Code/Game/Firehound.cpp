#include "Game/Firehound.hpp"
#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"

STATIC Firehound* Firehound::CreateFirehound() {
	Firehound* nEnemy = new Firehound();
	TheGame::RegisterEnemy(nEnemy);
	return nEnemy;
}

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Firehound::Firehound()
	: m_age(0.f)
{
	AABB2 bounds = TheSpriteRenderer::GetRect();

	m_position = Vector2(Randf(bounds.mins.x - 1.f, bounds.maxs.x + 1.f), bounds.maxs.y + 2.f);
	m_dest = Vector2(m_position.x, bounds.mins.y - 1.f);
	m_velocity = (m_dest - m_position) * ENEMY_FIREHOUND_MOVESPEED;

	Initialize(m_position, 0.f, "Firehound", "Foreground");
	m_physicsRadius = ENEMY_FIREHOUND_PHYSRADIUS;
	m_health = ENEMY_FIREHOUND_HEALTH;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void Firehound::Update(float deltaSeconds) {
	m_position = m_position + m_velocity * deltaSeconds;

	m_age += deltaSeconds;

	if (m_age >= ENEMY_FIREHOUND_FIRE_RATE) {
		m_age = 0.f;
		Fire();
	}

	if (m_position.y <= TheSpriteRenderer::GetRect().mins.y - 0.5f) {
		Kill();
	}

	Entity::Update(deltaSeconds);
}

void Firehound::Fire() {

	Vector2 fireVel = Vector2(0.f, -1.f) * ENEMY_FIREHOUND_BULLETSPEED;

	Projectile::CreateProjectile(m_position, fireVel, "PlayerProjectile", OWNER_AI);
	AudioSystem::PlayFire();
}

VIRTUAL void Firehound::Kill(bool playDeathEffect) {
	m_isAlive = false;
	TheGame::UnregisterEnemy(this);

	if (playDeathEffect) {
		SpawnDeathExplosion();
	}
}

VIRTUAL void Firehound::ApplyDamage(int damageDealt, eOwner bulletOwner) {
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