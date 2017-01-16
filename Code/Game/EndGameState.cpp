#include "Game/EndGameState.hpp"
#include "Game/MainMenuState.hpp"
#include "Game/TheGame.hpp"
#include "Engine/Renderer/Fonts/Font.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
EndGameState::EndGameState()
	: State("EndGameState")
{
	m_font = Font::CreateOrGetFont("Tahoma");
	m_gameOverScreen = Texture::CreateOrGetTexture("Data/Textures/GameOverScreen.png");

	m_scores[0].m_playerNum = 1;
	m_scores[0].m_playerScore = g_theGame->m_player1Ship->m_score;
	m_scores[1].m_playerNum = 2;
	m_scores[1].m_playerScore = g_theGame->m_player2Ship->m_score;
	m_scores[2].m_playerNum = 3;
	m_scores[2].m_playerScore = g_theGame->m_player3Ship->m_score;
	m_scores[3].m_playerNum = 4;
	m_scores[3].m_playerScore = g_theGame->m_player4Ship->m_score;

	qsort(m_scores, 4, sizeof(PlayerNumAndScore), ScoreComparator);

	g_theGame->RefreshGame();
	g_theGame->m_player1Ship->Refresh();
	g_theGame->m_player2Ship->Refresh();
	g_theGame->m_player3Ship->Refresh();
	g_theGame->m_player4Ship->Refresh();

	AudioSystem::PlayEndGameMusic();
}

//---------------------------------------------------------------------------------------------------------------------------
//ENTER UPDATE RENDER EXIT
//---------------------------------------------------------------------------------------------------------------------------
void EndGameState::Enter() {

}

State* EndGameState::Update(float deltaSeconds) {
	State* state = SwitchStates();
	if (nullptr == state) {
		UpdateEndGameState(deltaSeconds);
	}

	return state;
}
void EndGameState::UpdateEndGameState(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);
}

void EndGameState::Render() const {
	g_theRenderer->SetOrtho2D(Vector2(0.f, 0.f), Vector2(1600.f, 900.f));

	g_theRenderer->DrawTexturedAABB2(m_gameOverScreen, RGBA::WHITE, AABB2(Vector2(0.f, 0.f), Vector2(1600.f, 900.f)));

	String player1 = StringUtils::Stringf("PLAYER %i: %i", m_scores[0].m_playerNum, m_scores[0].m_playerScore);
	m_font->DrawText2D(Vector2(400.f, 350.f), player1, 1.f, RGBA::WHITE);


	if (g_theGame->m_playerCount >= 2) {
		String player2 = StringUtils::Stringf("PLAYER %i: %i", m_scores[1].m_playerNum, m_scores[1].m_playerScore);
		m_font->DrawText2D(Vector2(400.f, 300.f), player2, 1.f, RGBA::WHITE);
	}

	if (g_theGame->m_playerCount >= 3) {
		String player3 = StringUtils::Stringf("PLAYER %i: %i", m_scores[2].m_playerNum, m_scores[2].m_playerScore);
		m_font->DrawText2D(Vector2(400.f, 250.f), player3, 1.f, RGBA::WHITE);
	}

	if (g_theGame->m_playerCount >= 4) {
		String player4 = StringUtils::Stringf("PLAYER %i: %i", m_scores[3].m_playerNum, m_scores[3].m_playerScore);
		m_font->DrawText2D(Vector2(400.f, 200.f), player4, 1.f, RGBA::WHITE);
	}
}

bool EndGameState::Exit() {
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
State* EndGameState::SwitchStates() {

	if (g_theInputSystem->GetKeyDown(VK_RETURN)) {
		g_theGame->InitializePlayers();
		g_theGame->m_player1Ship->m_isEnabled = true;
		return new MainMenuState();
	}

	return nullptr;
}

int ScoreComparator(const void * score1, const void * score2) {
	PlayerNumAndScore* a = (PlayerNumAndScore*)score1;
	PlayerNumAndScore* b = (PlayerNumAndScore*)score2;
	return (b->m_playerScore - a->m_playerScore);
}