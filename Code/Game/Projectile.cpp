#include "Game/Projectile.hpp"
#include "Game/TheGame.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------------------------------
//STATICS
//---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
STATIC Projectile* Projectile::CreateProjectile(const Vector2& pos, const Vector2& vel, const String& name, eOwner owner) {
	Projectile* nProjectile = new Projectile(pos, vel, name, owner);

	(owner != OWNER_AI) ? (TheGame::RegisterPlayerProjectile(nProjectile)) : (TheGame::RegisterEnemyProjectile(nProjectile));
	return nProjectile;
}

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Projectile::Projectile(const Vector2& pos, const Vector2& vel, const String& name, eOwner owner) 
	: m_owner(owner)
{
	m_velocity = vel;
	float rot = atan2(vel.y, vel.x);
	Initialize(pos, rot, name, "Midground");
	m_sprite->m_scale = Vector2(0.05f, 0.06f);
	m_health = 0;
	m_physicsRadius = PROJECTILE_PHYSRADIUS;
}

void Projectile::Update(float deltaSeconds) {
	m_position += m_velocity * deltaSeconds;

	if (!IsDiskInSquare(m_position, m_physicsRadius, TheSpriteRenderer::GetRect())) {
		Kill();
	}
	
	Entity::Update(deltaSeconds);
}

VIRTUAL void Projectile::Kill(bool playDeathEffect) {
	m_isAlive = false;
	//m_sprite->Disable();
	(m_owner != OWNER_AI) ? (TheGame::UnregisterPlayerProjectile(this)) : (TheGame::UnregisterEnemyProjectile(this));
}