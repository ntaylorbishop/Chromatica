#include "Game/TornadoBoss.hpp"
#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"

STATIC TornadoBoss* TornadoBoss::CreateTornadoBoss() {
	TornadoBoss* nTornadoBoss = new TornadoBoss();
	TheGame::RegisterEnemy(nTornadoBoss);
	return nTornadoBoss;
}

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
TornadoBoss::TornadoBoss()
	: m_age(0.f)
	, m_currAngleStep(1.f)
	, m_currAngle(-90.f)
	, m_fireAge(0.f)
	, m_camAge(0.f)
{
	AABB2 bounds = TheSpriteRenderer::GetRect();

	m_position = Vector2(0.f, bounds.maxs.y + 5.f);
	m_dest = Vector2(0.f, bounds.maxs.y - 3.f);
	m_velocity = (m_dest - m_position) * ENEMY_TORNADOBOSS_MOVESPEED;

	Initialize(m_position, 0.f, "TornadoBoss", "Foreground");
	m_physicsRadius = ENEMY_TORNADOBOSS_PHYSRADIUS;
	m_health = ENEMY_TORNADOBOSS_HEALTH;
	m_sprite->m_scale = Vector2(9.f, 4.f);
}
TornadoBoss::~TornadoBoss() {
	g_theGame->m_player1Ship->Upgrade();
	g_theGame->m_player2Ship->Upgrade();
	g_theGame->m_player3Ship->Upgrade();
	g_theGame->m_player4Ship->Upgrade();
	g_theGame->m_camera2D.SetPosition(Vector3(0.f, 0.f, 0.f));
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void TornadoBoss::Update(float deltaSeconds) {
	m_position = m_position + m_velocity * deltaSeconds;
	m_age += deltaSeconds;
	m_fireAge += deltaSeconds;
	m_camAge += deltaSeconds * 20.f;

	if ((m_position - m_dest).Length() <= 0.05f) {
		m_velocity = Vector2::ZERO;
	}

	//y = (x++ % 6) < 3 ? 3 : 0;

	if (m_velocity.x == 0.f && m_velocity.y == 0.f) {
		m_age += deltaSeconds;

		if (m_fireAge >= 3.f) {
			if (m_age >= ENEMY_TORNADOBOSS_FIRE_RATE) {
				Fire(deltaSeconds);
				m_age = 0.f;
			}
		}
	}

	if (m_fireAge >= 6.f) {
		m_fireAge = 0.f;
	}

	g_theGame->m_camera2D.SetPosition(Vector3(0.1f * cos(m_camAge), 0.f, 0.f));
	Entity::Update(deltaSeconds);
}

void TornadoBoss::Fire(float deltaSeconds) {

	UNREFERENCED_PARAMETER(deltaSeconds);

	if (m_currAngle < -45.f && m_currAngle > -135.f) {
		float xVel = CosDegrees(m_currAngle);
		float yVel = SinDegrees(m_currAngle);

		Vector2 fireVel = Vector2(xVel, yVel) * ENEMY_TORNADOBOSS_BULLETSPEED;

		Projectile::CreateProjectile(m_position, fireVel, "PlayerProjectile", OWNER_AI);

	}
	if (m_currAngle > -45.f) {
		m_currAngleStep = -1.f;
	}
	else if(m_currAngle < -135.f) {
		m_currAngleStep = 1.f;
	}
	m_currAngle += 9.f * m_currAngleStep;
	AudioSystem::PlayFire();
}

VIRTUAL void TornadoBoss::Kill(bool playDeathEffect) {
	m_isAlive = false;
	TheGame::UnregisterEnemy(this);

	if (playDeathEffect) {
		SpawnDeathExplosion();
	}
}

VIRTUAL void TornadoBoss::ApplyDamage(int damageDealt, eOwner bulletOwner) {
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