#include "Game/TheStarryBackground.hpp"
#include "Engine/General/Logger/TheLogger.hpp"
#include "Engine/Renderer/SpriteRenderer/TheSpriteRenderer.hpp"
#include "Game/GameParticle.hpp"
#include "Engine/General/Core/GameEngine.hpp"

STATIC TheStarryBackground* TheStarryBackground::s_theStarryBackground = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------------------------------
//STATICS
//---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
STATIC void TheStarryBackground::Initialize() {
	if (s_theStarryBackground) {
		LogPrintf("StarryBackground has already been initialized.", "General", LOG_ALL);
	}
	else {
		s_theStarryBackground = new TheStarryBackground();
		g_theApparatusEngine->RegisterUpdateCallback(MakeDelegate(s_theStarryBackground, &TheStarryBackground::Update));
	}
}
STATIC void TheStarryBackground::Destroy() {
	if (!s_theStarryBackground) {
		LogPrintf("Cannot delete StarryBackground, has already been deleted.", "General", LOG_ALL);
	}
	else {
		delete s_theStarryBackground;
		s_theStarryBackground = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TheStarryBackground::TheStarryBackground() 
	: m_age(0.f)
{

/*
	AABB2 screenRect = TheSpriteRenderer::GetRect();

	for (uint i = 0; i < 100; i++) {
		Vector2 spawnPos = Vector2(Randf(screenRect.mins.x, screenRect.maxs.x), Randf(screenRect.mins.y, screenRect.maxs.y));
		Particle* nPos = new Particle(spawnPos, Vector2(0.f, -0.01f), "PlayerProjectile");
	}*/
}
TheStarryBackground::~TheStarryBackground() {

}

void TheStarryBackground::Update(float deltaSeconds) {

	UNREFERENCED_PARAMETER(deltaSeconds);

	m_age += (float)m_clock.GetDelta();

	if (m_age >= 0.07f) {
		m_age = 0.f;
		SpawnStar();
		SpawnStar();
	}
}
void TheStarryBackground::SpawnStar() {
	AABB2 screenRect = TheSpriteRenderer::GetRect();
	Vector2 pos = Vector2(Randf(screenRect.mins.x, screenRect.maxs.x), screenRect.maxs.y + 0.5f);
	Vector2 vel = Vector2(0.f, -Randf(0.1f, 10.f));

	GameParticle* nParticle = new GameParticle(pos, vel, "PlayerProjectile");
	UNREFERENCED_PARAMETER(nParticle);
}