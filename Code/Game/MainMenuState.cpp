#include "Game/MainMenuState.hpp"
#include "Game/PlayingGameState.hpp"
#include "Engine/General/Core/GameEngine.hpp"
#include "Game/TheGame.hpp"
#include "Game/EndGameState.hpp"
#include "Engine/Renderer/SpriteRenderer/ParticleSystem/ParticleSystem.hpp"
#include "Engine/Renderer/SpriteRenderer/Sprite.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
MainMenuState::MainMenuState()
	: State("MainMenu")
	, m_font(nullptr)
	, m_logo1(nullptr)
	, m_logo2(nullptr)
	, m_whichLogo(false)
	, m_age(0.f)
{

	m_clock = Clock(nullptr, 3.f);
	m_font = Font::CreateOrGetFont("Tahoma");
	AudioSystem::PlayGameIntroLoop();

	m_logo1 = Texture::CreateOrGetTexture("Data/Textures/Logo1.png");
	m_logo2 = Texture::CreateOrGetTexture("Data/Textures/Logo2.png");

	m_logoSprite = Sprite::CreateSprite("Logo1", "Logo");
	m_logoSprite->Enable();
	m_logoSprite->m_position = Vector2(0.f, 0.f);
}

//---------------------------------------------------------------------------------------------------------------------------
//ENTER UPDATE RENDER EXIT
//---------------------------------------------------------------------------------------------------------------------------
void MainMenuState::Enter() {

}

State* MainMenuState::Update(float deltaSeconds) {
	State* state = SwitchStates();
	if (nullptr == state) {
		UpdateMainMenu(deltaSeconds);
	}

	if (m_clock.GetCurrent() >= 2.f) {
		m_whichLogo = !m_whichLogo;

		if (m_whichLogo) {
			Sprite::Delete(m_logoSprite);
			m_logoSprite = Sprite::CreateSprite("Logo1", "Logo");
			m_logoSprite->Enable();
			m_logoSprite->m_position = Vector2(0.f, 0.f);
		}
		else {
			Sprite::Delete(m_logoSprite);
			m_logoSprite = Sprite::CreateSprite("Logo2", "Logo");
			m_logoSprite->Enable();
			m_logoSprite->m_position = Vector2(0.f, 0.f);
		}

		m_clock.Reset();
	}

	return state;
}
void MainMenuState::UpdateMainMenu(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);
}

void MainMenuState::Render() const {

	g_theRenderer->SetOrtho2D(Vector2(0.f, 0.f), g_theRenderer->GetScreenSize());
	Vector2 screenSize = g_theRenderer->GetScreenSize();

	Vector2 dims = Vector2(1400, 310);
	AABB2 quad = AABB2(Vector2(screenSize.x / 2.f - dims.x / 2.f, screenSize.y / 2.f - dims.y / 2.f), Vector2(screenSize.x / 2.f + dims.x / 2.f, screenSize.y / 2.f + dims.y / 2.f));
}

bool MainMenuState::Exit() {
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
State* MainMenuState::SwitchStates() {
	if (g_theInputSystem->GetKeyDown(VK_RETURN) 
		|| g_theGame->m_player1Ship->m_controller.GetButtonDown(XB_START)
		|| g_theGame->m_player2Ship->m_controller.GetButtonDown(XB_START)
		|| g_theGame->m_player3Ship->m_controller.GetButtonDown(XB_START)
		|| g_theGame->m_player4Ship->m_controller.GetButtonDown(XB_START))
	{
		Sprite::Delete(m_logoSprite);
		return new PlayingGameState();
	}
	else if (g_theInputSystem->GetKeyDown(VK_ESCAPE)) {
		if (!g_theApparatusEngine->IsConsoleOpen()) {
			g_theInputSystem->Quitting(true);
		}
	}

	return nullptr;
}