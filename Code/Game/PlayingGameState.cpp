#include "Game/PlayingGameState.hpp"
#include "Game/NightmareBoss.hpp"
#include "Game/TheGame.hpp"
#include "Game/Projectile.hpp"
#include "Game/EndGameState.hpp"
#include "Game/TheUI.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
PlayingGameState::PlayingGameState()
	: State("PlayingGameState")
	, m_age(0.f)
	, m_isStillAlive(true)
{
	m_levelStateMachine = LevelStateMachine();
	g_theGame->m_player1Ship->m_sprite->Enable();

	g_theUI->m_isEnabled = true;

	AudioSystem::PlayGameMusicLoop();
}
PlayingGameState::~PlayingGameState() {
	g_theUI->m_isEnabled = false;
}

//---------------------------------------------------------------------------------------------------------------------------
//ENTER UPDATE RENDER EXIT
//---------------------------------------------------------------------------------------------------------------------------
void PlayingGameState::Enter() {

}

State* PlayingGameState::Update(float deltaSeconds) {
	State* state = SwitchStates();
	if (nullptr == state) {
		m_levelStateMachine.Update(deltaSeconds);
		UpdatePlayingGame(deltaSeconds);
	}

	return state;
}
void PlayingGameState::UpdatePlayingGame(float deltaSeconds) {

	g_theGame->HandleCollisions(deltaSeconds);
}

void PlayingGameState::Render() const { 

	g_theRenderer->SetOrtho2D(Vector2(0.f, 0.f), g_theRenderer->GetScreenSize());
}

bool PlayingGameState::Exit() {
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
State* PlayingGameState::SwitchStates() {

	if (g_theGame->m_player1Ship->IsDead()
		&& g_theGame->m_player1Ship->IsDead()
		&& g_theGame->m_player1Ship->IsDead()
		&& g_theGame->m_player1Ship->IsDead())
	{
		return new EndGameState();
	}

	return nullptr;
}