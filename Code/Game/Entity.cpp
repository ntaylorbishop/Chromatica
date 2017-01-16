#include "Game/Entity.hpp" 
#include "Game/GameParticle.hpp"



//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Entity::Entity() 
	: m_position(Vector2())
	, m_rotation(0.f)
	, m_sprite(nullptr)
	, m_physicsRadius(0.f)
	, m_health(0)
{ }
Entity::~Entity() {
	Sprite::Delete(m_sprite);
	EntitySystem::UnregisterEntity(this);
}

VIRTUAL void Entity::Initialize(const Vector2& pos, float rotation, const String& spriteName, const String& layerName) {
	m_position = pos;
	m_rotation = rotation;
	m_sprite = Sprite::CreateSprite(spriteName, layerName);
	m_sprite->Enable();
	m_sprite->m_position = m_position;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
VIRTUAL void Entity::Update(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);
	m_sprite->m_position = m_position;
	m_sprite->m_rotation = m_rotation;
}

//---------------------------------------------------------------------------------------------------------------------------
//GETTERS SETTERS
//---------------------------------------------------------------------------------------------------------------------------

void Entity::SetPosition(const Vector2& pos) {
	m_position = pos;
	m_sprite->m_position = pos;
}
VIRTUAL void Entity::ApplyDamage(int damageDealt) {
	m_health -= damageDealt;

	if (m_health <= 0) {
		m_isAlive = false;
		Kill();
	}
}

VIRTUAL void Entity::SpawnDeathExplosion() {

	for (uint i = 0; i < 30; i++) {
		float velScale = Randf(3.f, 10.f);
		Vector2 vel = Vector2(Randf(-1.f, 1.f), Randf(-1.f, 1.f) * velScale);
		GameParticle* nParticle = new GameParticle(m_position, vel, "PlayerProjectile");
		nParticle->m_sprite->m_scale = Vector2(0.01f, 0.01f);
		nParticle->m_isFading = true;
	}
}