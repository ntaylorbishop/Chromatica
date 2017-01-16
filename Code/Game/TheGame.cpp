#include "Engine/General/Profiler/Profiler.hpp"
#include "Game/TheGame.hpp"
#include "Game/MaterialManager.hpp"
#include "Game/TheStarryBackground.hpp"
#include "Game/Projectile.hpp"
#include "Game/GameParticle.hpp"

TheGame* g_theGame = nullptr;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS INITIALIZATION
//---------------------------------------------------------------------------------------------------------------------------
TheGame::TheGame() 
	: m_camera2D()
	, m_gameStateMachine(nullptr)
	, m_player1Ship(nullptr)
	, m_player2Ship(nullptr)
	, m_player3Ship(nullptr)
	, m_player4Ship(nullptr)
	, m_playerProjectiles()
	, m_enemies()
	, m_projectiles()
	, m_playerCount(1)
{
	AudioSystem::Initialize();
	InitializeSpriteRenderer();
	m_gameStateMachine = new ChromaticaStateMachine();
	g_theMaterialManager = new MaterialManager();
	g_theApparatusEngine->BindKeyToConsole(VK_F1);
	InitializeEntitySystem();
	InitializePlayers();
	TheStarryBackground::Initialize();

	for (uint i = 0; i < MAX_NUM_PROJECTILES; i++) {
		m_projectiles[i] = nullptr;
	}
	for (uint i = 0; i < MAX_NUM_ENEMIES; i++) {
		m_enemies[i] = nullptr;
	}
	for (uint i = 0; i < MAX_NUM_PLAYERPROJECTILES; i++) {
		m_playerProjectiles[i] = nullptr;
	}
}
TheGame::~TheGame() {
	AudioSystem::Destroy();
	TheSpriteRenderer::Destroy();
	EntitySystem::Destroy();
	TheStarryBackground::Destroy();
	delete m_gameStateMachine;
	m_gameStateMachine = nullptr;
}

void TheGame::InitializeEntitySystem() {
	EntitySystem::Initialize();
}
void TheGame::InitializeSpriteRenderer() {
	////////////////////////////////////////////////////
	//------------------------------------------
	//INITIALIZING SPRITES
	TheSpriteRenderer::Initialize(10.f, g_theRenderer->GetScreenSize().x / g_theRenderer->GetScreenSize().y);
	TheSpriteRenderer::SetImportSize(256.f);
	TheSpriteRenderer::CreateLayer("Background");
	TheSpriteRenderer::CreateLayer("Midground");
	TheSpriteRenderer::CreateLayer("Foreground");
	TheSpriteRenderer::CreateLayer("Logo");


	SpriteDatabase::RegisterSprite("NightmareBoss", "Data/Sprites/BOSS_Type3_Skullplate.png");
	SpriteDatabase::RegisterSprite("Firefly", "Data/Sprites/ENM_Type4_Firefly.png");
	SpriteDatabase::RegisterSprite("Firehound", "Data/Sprites/ENM_Type5_DoubleDecker.png");
	SpriteDatabase::RegisterSprite("Hellhound", "Data/Sprites/ENM_Type1_Armorbeetle.png");
	SpriteDatabase::RegisterSprite("Player1", "Data/Sprites/PlayerShip1_Center.png");
	SpriteDatabase::RegisterSprite("Player2", "Data/Sprites/ENM_Type5_MicroFighter.png");
	SpriteDatabase::RegisterSprite("Player3", "Data/Sprites/ENM_Type1_Scarab.png");
	SpriteDatabase::RegisterSprite("Player4", "Data/Sprites/ENM_Type2_Stealth.png");
	SpriteDatabase::RegisterSprite("PlayerProjectile", "Data/Sprites/ShipProjectile.png");
	SpriteDatabase::RegisterSprite("TornadoBoss", "Data/Sprites/BOSS_Type6_Tornado.png");
	SpriteDatabase::RegisterSprite("Plaguebringer", "Data/Sprites/ENM_Type3_Plaguebringer.png");
	SpriteDatabase::RegisterSprite("Bugzapper", "Data/Sprites/ENM_Type4_Quadshot.png");
	SpriteDatabase::RegisterSprite("ExplosionParticle", "Data/Sprites/ExplosionParticle.png");

	SpriteDatabase::RegisterSprite("Logo1", "Data/Textures/Logo1.png");
	SpriteDatabase::RegisterSprite("Logo2", "Data/Textures/Logo2.png");
	SpriteDatabase::EditSpriteResource("Logo1")->m_dimensions = Vector2(13.548f, 3.f);
	SpriteDatabase::EditSpriteResource("Logo2")->m_dimensions = Vector2(13.548f, 3.f);


	////////////////////////////////////////////////////
	//------------------------------------------
	//INITIALIZING PARTICLE SYSTEMS
	ParticleSystemDefinition* explosion = ParticleSystemDefinition::RegisterParticleSystemDefinition("Explosion");
	ParticleEmitterDefinition* explode = explosion->AddEmitter(ParticleEmitterDefinition::Create("Explosion", "ExplosionParticle"));
	explode->m_blendMode = BLENDMODE_ALPHABLEND;
	explode->m_initialSpawnCount = RangeInt(5, 10);
	explode->m_spawnRate = 0.f;
	explode->m_life = RangeFloat(0.5f, 1.f);
	explode->m_initialScale = RangeFloat(0.05f, 0.12f);
	explode->m_tint = RGBA::WHITE;
	explode->m_startVelocity = RangeVector2(Vector2(-1.f, -1.f), Vector2(1.f, 1.f));
	explode->m_velocityStrength = RangeFloat(5.f, 10.f);
	explode->m_acceleration = RangeVector2(Vector2::ZERO, Vector2::ZERO);



	////////////////////////////////////////////////////
	//------------------------------------------
	//INIT CAMERA
	m_camera2D = Camera2D(Vector2(0.f, 0.f), 0.f, AABB2(Vector2(-10.f, -10.f), Vector2(10.f, 10.f)));
}
void TheGame::InitializePlayers() {

	m_player1Ship = PlayerShip::CreatePlayerShip(0, RGBA::WHITE);
	m_player2Ship = PlayerShip::CreatePlayerShip(1, RGBA::WHITE);
	m_player3Ship = PlayerShip::CreatePlayerShip(2, RGBA::WHITE);
	m_player4Ship = PlayerShip::CreatePlayerShip(3, RGBA::WHITE);
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::Update(float deltaSeconds) {

	Profiler::PushFrame("TheGameUpdate");

	m_playerCount = 1;

	if (m_player2Ship->m_isEnabled)
		m_playerCount++;

	if (m_player3Ship->m_isEnabled)
		m_playerCount++;

	if (m_player4Ship->m_isEnabled)
		m_playerCount++;

	m_gameStateMachine->Update(deltaSeconds);

	Profiler::PopFrame();
}

void TheGame::HandleCollisions(float deltaSeconds) {

	UNREFERENCED_PARAMETER(deltaSeconds);

	for (uint i = 0; i < MAX_NUM_PLAYERPROJECTILES; i++) {
		Projectile* currProjectile = (Projectile*)m_playerProjectiles[i];

		if (!currProjectile)
			continue;

		for (uint j = 0; j < MAX_NUM_ENEMIES; j++) {

			if (!m_enemies[j])
				continue;

			if (DoDiscsOverlap(currProjectile->m_position, currProjectile->m_physicsRadius, m_enemies[j]->m_position, m_enemies[j]->m_physicsRadius)) {
				SpawnParticleExplosion(currProjectile->m_position, currProjectile->m_velocity);
				currProjectile->Kill();
				m_enemies[j]->ApplyDamage(PLAYER_DAMAGE, currProjectile->m_owner);
				AudioSystem::PlayHit();
				break;
			}
		}
	}

	for (uint i = 0; i < MAX_NUM_PROJECTILES; i++) {
		Projectile* currProjectile = (Projectile*)m_projectiles[i];

		if (!currProjectile)
			continue;

		if (!m_player1Ship->m_hasDied && DoDiscsOverlap(currProjectile->m_position, currProjectile->m_physicsRadius, m_player1Ship->m_position, m_player1Ship->m_physicsRadius)) {
			SpawnParticleExplosion(currProjectile->m_position, currProjectile->m_velocity);
			currProjectile->Kill();
			m_player1Ship->ApplyDamage(PLAYER_DAMAGE_TAKEN);
			AudioSystem::PlayHit();
		}

		if (!m_player2Ship->m_hasDied && DoDiscsOverlap(currProjectile->m_position, currProjectile->m_physicsRadius, m_player2Ship->m_position, m_player2Ship->m_physicsRadius)) {
			SpawnParticleExplosion(currProjectile->m_position, currProjectile->m_velocity);
			currProjectile->Kill();
			m_player2Ship->ApplyDamage(PLAYER_DAMAGE_TAKEN);
			AudioSystem::PlayHit();
		}

		if (!m_player3Ship->m_hasDied && DoDiscsOverlap(currProjectile->m_position, currProjectile->m_physicsRadius, m_player3Ship->m_position, m_player3Ship->m_physicsRadius)) {
			SpawnParticleExplosion(currProjectile->m_position, currProjectile->m_velocity);
			currProjectile->Kill();
			m_player3Ship->ApplyDamage(PLAYER_DAMAGE_TAKEN);
			AudioSystem::PlayHit();
		}

		if (!m_player4Ship->m_hasDied && DoDiscsOverlap(currProjectile->m_position, currProjectile->m_physicsRadius, m_player4Ship->m_position, m_player4Ship->m_physicsRadius)) {
			SpawnParticleExplosion(currProjectile->m_position, currProjectile->m_velocity);
			currProjectile->Kill();
			m_player4Ship->ApplyDamage(PLAYER_DAMAGE_TAKEN);
			AudioSystem::PlayHit();
		}
	}

	for (uint i = 0; i < MAX_NUM_ENEMIES; i++) {

		Entity*& currEnemy = (Entity*)m_enemies[i];

		if (!currEnemy)
			continue;

		float y = TheSpriteRenderer::GetRect().mins.y;

		if (currEnemy->m_position.y + currEnemy->m_physicsRadius < TheSpriteRenderer::GetRect().mins.y) {
			currEnemy->Kill();
			continue;
		}

		if (!m_player1Ship->m_hasDied && DoDiscsOverlap(currEnemy->m_position, currEnemy->m_physicsRadius, m_player1Ship->m_position, m_player1Ship->m_physicsRadius)) {
			SpawnParticleExplosion(currEnemy->m_position, Vector2::ZERO);
			currEnemy->Kill();
			m_player1Ship->ApplyDamage(PLAYER_DAMAGE_TAKEN);
			AudioSystem::PlayHit();
			continue;
		}

		if (!m_player2Ship->m_hasDied && DoDiscsOverlap(currEnemy->m_position, currEnemy->m_physicsRadius, m_player2Ship->m_position, m_player2Ship->m_physicsRadius)) {
			SpawnParticleExplosion(currEnemy->m_position, Vector2::ZERO);
			currEnemy->Kill();
			m_player2Ship->ApplyDamage(PLAYER_DAMAGE_TAKEN);
			AudioSystem::PlayHit();
			continue;
		}

		if (!m_player3Ship->m_hasDied && DoDiscsOverlap(currEnemy->m_position, currEnemy->m_physicsRadius, m_player3Ship->m_position, m_player3Ship->m_physicsRadius)) {
			SpawnParticleExplosion(currEnemy->m_position, Vector2::ZERO);
			currEnemy->Kill();
			m_player3Ship->ApplyDamage(PLAYER_DAMAGE_TAKEN);
			AudioSystem::PlayHit();
			continue;
		}

		if (!m_player4Ship->m_hasDied && DoDiscsOverlap(currEnemy->m_position, currEnemy->m_physicsRadius, m_player4Ship->m_position, m_player4Ship->m_physicsRadius)) {
			SpawnParticleExplosion(currEnemy->m_position, Vector2::ZERO);
			currEnemy->Kill();
			m_player4Ship->ApplyDamage(PLAYER_DAMAGE_TAKEN);
			AudioSystem::PlayHit();
			continue;
		}
	}
}
void TheGame::SpawnParticleExplosion(const Vector2& pos, const Vector2& genVel) {

	float angle = ToDegrees(atan2(genVel.y, genVel.x));
	for (uint i = 0; i < 10; i++) {

		float speed = Randf(2.f, 4.f);
		float nAngle = Randf(angle - 45.f, angle + 45.f);
		Vector2 addedVel = Vector2(CosDegrees(nAngle), SinDegrees(nAngle)) * speed;
		GameParticle* nParticle = new GameParticle(pos, addedVel, "PlayerProjectile");
		nParticle->m_sprite->m_scale = Vector2(0.01f, 0.01f);
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::Render() const {
	TheSpriteRenderer::Render();
	m_gameStateMachine->Render();
}

//---------------------------------------------------------------------------------------------------------------------------
//ENTITY REGISTRATION
//---------------------------------------------------------------------------------------------------------------------------
//ENTITY REGISTRATION
STATIC void TheGame::RegisterPlayerProjectile(Projectile* nProjectile) {
	g_theGame->RegisterEntity(nProjectile, g_theGame->m_playerProjectiles, MAX_NUM_PLAYERPROJECTILES);
}
STATIC void TheGame::RegisterEnemy(Entity* nEnemy) {
	g_theGame->RegisterEntity(nEnemy, g_theGame->m_enemies, MAX_NUM_ENEMIES);
}
STATIC void TheGame::RegisterEnemyProjectile(Projectile* nEnemyProjectile) {
	g_theGame->RegisterEntity(nEnemyProjectile, g_theGame->m_projectiles, MAX_NUM_PROJECTILES);
}

STATIC void TheGame::UnregisterPlayerProjectile(Projectile* projectile) {
	g_theGame->UnregisterEntity(projectile, g_theGame->m_playerProjectiles, MAX_NUM_PLAYERPROJECTILES);
}
STATIC void TheGame::UnregisterEnemy(Entity* enemy) {
	g_theGame->UnregisterEntity(enemy, g_theGame->m_enemies, MAX_NUM_ENEMIES);
}
STATIC void TheGame::UnregisterEnemyProjectile(Projectile* enemyProjectile) {
	g_theGame->UnregisterEntity(enemyProjectile, g_theGame->m_projectiles, MAX_NUM_PROJECTILES);
}

void TheGame::RegisterEntity(Entity* entity, Entity** list, uint listSize) {
	uint idx = 0;
	for (idx = 0; idx < listSize; idx++) {
		if (list[idx] == nullptr) {
			break;
		}
	}
	if (idx != listSize) {
		list[idx] = entity;
		//DebuggerPrintf("Sup dawg");
	}
}
void TheGame::UnregisterEntity(Entity* entity, Entity** list, uint listSize) {
	for (uint i = 0; i < listSize; i++) {
		if (list[i] == entity) {
			list[i] = nullptr;
		}
	}

	//ERROR_AND_DIE("Couldn't unregister");
}

void TheGame::RefreshGame() {
	for (uint i = 0; i < MAX_NUM_PROJECTILES; i++) {
		if (m_projectiles[i])
			delete m_projectiles[i];
		m_projectiles[i] = nullptr;
	}
	for (uint i = 0; i < MAX_NUM_ENEMIES; i++) {
		if (m_enemies[i])
			delete m_enemies[i];
		m_enemies[i] = nullptr;
	}
	for (uint i = 0; i < MAX_NUM_PLAYERPROJECTILES; i++) {
		if (m_playerProjectiles[i])
			delete m_playerProjectiles[i];
		m_playerProjectiles[i] = nullptr;
	}
}