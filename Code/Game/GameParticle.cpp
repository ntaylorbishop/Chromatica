#include "Game/GameParticle.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
GameParticle::GameParticle(const Vector2& pos, const Vector2& vel, const String& name)
	: m_isFading(false)
{
	m_velocity = vel;
	float rot = atan2(vel.y, vel.x);
	Initialize(pos, rot, name, "Midground");
	m_sprite->m_scale = Vector2(0.01f, 0.01f);
}

void GameParticle::Update(float deltaSeconds) {
	m_position += m_velocity * deltaSeconds;

	if (m_isFading) {
		RGBA currSpriteCol = m_sprite->m_tint;
		m_sprite->m_tint = RGBA(currSpriteCol.r, currSpriteCol.g, currSpriteCol.b, currSpriteCol.a - deltaSeconds);
	}

	AABB2 rect = TheSpriteRenderer::GetRect();
	rect.mins = rect.mins + Vector2(-1.f, -1.f);
	rect.maxs = rect.maxs + Vector2(1.f, 1.f);

	if (!IsDiskInSquare(m_position, m_physicsRadius, rect)) {
		m_isAlive = false;
	}

	Entity::Update(deltaSeconds);
}

VIRTUAL void GameParticle::Kill(bool playDeathEffect) {
	m_isAlive = false;
}