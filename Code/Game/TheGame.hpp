#pragma once

#include "Engine/General/Core/GameEngine.hpp"
#include "Engine/EntitySystem/EntitySystem.hpp"
#include "Engine/Renderer/Camera2D.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/SpriteRenderer/TheSpriteRenderer.hpp"
#include "Engine/Renderer/SpriteRenderer/SpriteDatabase.hpp"
#include "Engine/Renderer/SpriteRenderer/Sprite.hpp"
#include "Engine/Renderer/SpriteRenderer/ParticleSystem/ParticleSystemDefinition.hpp"
#include "Engine/Renderer/SpriteRenderer/ParticleSystem/ParticleEmitterDefinition.hpp"
#include "Game/PlayerShip.hpp"
#include "Game/ChromaticaStateMachine.hpp"
#include "Game/AudioSystem.hpp"

class Projectile;
class TheGame;
extern TheGame* g_theGame;

const uint MAX_NUM_ENEMIES = 1000;
const uint MAX_NUM_PROJECTILES = 10000;
const uint MAX_NUM_PLAYERPROJECTILES = 10000;

class TheGame {
public:
	//ENTITY REGISTRATION
	static void RegisterPlayerProjectile(Projectile* nProjectile);
	static void RegisterEnemy(Entity* nEnemy);
	static void RegisterEnemyProjectile(Projectile* nEnemyProjectile);
	static void UnregisterPlayerProjectile(Projectile* projectile);
	static void UnregisterEnemy(Entity* enemy);
	static void UnregisterEnemyProjectile(Projectile* enemyProjectile);

	//STRUCTORS INITIALIZATION
	TheGame();
	~TheGame();

	void InitializeSpriteRenderer();
	void InitializeEntitySystem();
	void InitializePlayers();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	//HANDLE ENTITIES
	void HandleCollisions(float deltaSeconds);
	void SpawnParticleExplosion(const Vector2& pos, const Vector2& genVel);

	void RefreshGame();


	PlayerShip* m_player1Ship;
	PlayerShip* m_player2Ship;
	PlayerShip* m_player3Ship;
	PlayerShip* m_player4Ship;

	Entity* m_playerProjectiles[MAX_NUM_PLAYERPROJECTILES];
	Entity* m_enemies[MAX_NUM_ENEMIES];
	Entity* m_projectiles[MAX_NUM_PROJECTILES];
	Camera2D m_camera2D;
	int m_playerCount;

private:
	ChromaticaStateMachine* m_gameStateMachine;

	void RegisterEntity(Entity* entity, Entity** list, uint listSize);
	void UnregisterEntity(Entity* entity, Entity** list, uint listSize);

	float m_age;
};

//CONSOLE COMMANDS