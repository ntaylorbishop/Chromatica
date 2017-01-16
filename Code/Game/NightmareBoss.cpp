#include "Game/NightmareBoss.hpp"
#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"

STATIC NightmareBoss* NightmareBoss::CreateNightmareBoss() {
	NightmareBoss* nNightmareBoss = new NightmareBoss();
	TheGame::RegisterEnemy(nNightmareBoss);
	return nNightmareBoss;
}

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
NightmareBoss::NightmareBoss() 
	: m_age(0.f)
{
	AABB2 bounds = TheSpriteRenderer::GetRect();

	m_position = Vector2(Randf(bounds.mins.x - 1.f, bounds.maxs.x + 1.f), bounds.maxs.y + 2.f);
	m_dest = Vector2(Randf(bounds.mins.x + 2.f, bounds.maxs.x - 2.f), Randf(bounds.mins.y + 4.f, bounds.maxs.y - 2.f));
	m_velocity = (m_dest - m_position) * ENEMY_NIGHTMAREBOSS_MOVESPEED;

	Initialize(m_position, 0.f, "NightmareBoss", "Foreground");
	m_physicsRadius = ENEMY_NIGHTMAREBOSS_PHYSRADIUS;
	m_health = ENEMY_NIGHTMAREBOSS_HEALTH;
	m_sprite->m_scale = Vector2(2.f, 2.f);
}
NightmareBoss::~NightmareBoss() {
	g_theGame->m_player1Ship->Upgrade();
	g_theGame->m_player2Ship->Upgrade();
	g_theGame->m_player3Ship->Upgrade();
	g_theGame->m_player4Ship->Upgrade();

}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void NightmareBoss::Update(float deltaSeconds) {
	m_position = m_position + m_velocity * deltaSeconds;
	
	if ((m_position - m_dest).Length() <= 0.05f) {
		m_velocity = Vector2::ZERO;
	}

	if (m_velocity.x == 0.f && m_velocity.y == 0.f) {
		m_age += deltaSeconds;

		if (m_age >= ENEMY_NIGHTMAREBOSS_FIRE_RATE) {
			m_age = 0.f;
			Fire();
		}
	}

	Entity::Update(deltaSeconds);
}

void NightmareBoss::Fire() {
	float bulletsFired = Randf(20.f, 30.f);
	float angleStep = 360.f / (float)bulletsFired;
	float startingAngle = Randf(0.f, 45.f);

	for (float angle = 0.f; angle < startingAngle + 360.f; angle += angleStep) {
		float xVel = CosDegrees(angle);
		float yVel = SinDegrees(angle);

		Vector2 fireVel = Vector2(xVel, yVel) * ENEMY_NIGHTMAREBOSS_BULLETSPEED;
		
		Projectile::CreateProjectile(m_position, fireVel, "PlayerProjectile", OWNER_AI);
	}
	AudioSystem::PlayFire();
}

VIRTUAL void NightmareBoss::Kill(bool playDeathEffect) {
	m_isAlive = false;
	TheGame::UnregisterEnemy(this);

	if (playDeathEffect) {
		SpawnDeathExplosion();
	}
}

VIRTUAL void NightmareBoss::ApplyDamage(int damageDealt, eOwner bulletOwner) {
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