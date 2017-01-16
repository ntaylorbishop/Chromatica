#include "Game/TheUI.hpp"
#include "Game/TheGame.hpp"

TheUI* g_theUI = nullptr;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
TheUI::TheUI() 
{
	m_squirrelFont = BitmapFont::CreateOrGetFont("SquirrelFixedFont");
	m_font = Font::CreateOrGetFont("Tahoma");
	m_isEnabled = false;
}
TheUI::~TheUI() {
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheUI::Update(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);

}
void TheUI::Render() const {
	if (m_isEnabled) {
		g_theRenderer->SetOrtho2D(Vector2(0.f, 0.f), Vector2(1600.f, 900.f));
		//RenderDebugText();
		RenderScores();
	}
}
//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE
//---------------------------------------------------------------------------------------------------------------------------
void TheUI::RenderDebugText() const {		

	String sampleText = StringUtils::Stringf("%i", 1000);
	m_squirrelFont->DrawText2D(Vector2(10.f, 850.f), sampleText, 0.4f, RGBA::WHITE);
}

void TheUI::RenderScores() const {
	//PLAYER 1
	String p1Score = StringUtils::Stringf("PLAYER 1: %i", g_theGame->m_player1Ship->m_score);
	String p1Name = StringUtils::Stringf("LIVES: %i", g_theGame->m_player1Ship->m_remainingLives);
	m_font->DrawText2D(Vector2(15.f, 865.f), p1Score, 0.4f, RGBA::WHITE);
	m_font->DrawText2D(Vector2(15.f, 845.f), p1Name, 0.4f, RGBA::WHITE);

	//PLAYER 2
	if (g_theGame->m_player2Ship->m_isEnabled) {
		String p2Score = StringUtils::Stringf("PLAYER 2: %i", g_theGame->m_player2Ship->m_score);
		String p2Name = StringUtils::Stringf("LIVES: %i", g_theGame->m_player2Ship->m_remainingLives);
		m_font->DrawText2D(Vector2(1410.f, 865.f), p2Score, 0.4f, RGBA::WHITE);
		m_font->DrawText2D(Vector2(1500.f, 845.f), p2Name, 0.4f, RGBA::WHITE);
	}

	//PLAYER 3
	if (g_theGame->m_player3Ship->m_isEnabled) {
		String p3Score = StringUtils::Stringf("PLAYER 3: %i", g_theGame->m_player3Ship->m_score);
		String p3Name = StringUtils::Stringf("LIVES: %i", g_theGame->m_player3Ship->m_remainingLives);
		m_font->DrawText2D(Vector2(5.f, 35.f), p3Score, 0.4f, RGBA::WHITE);
		m_font->DrawText2D(Vector2(5.f, 15.f), p3Name, 0.4f, RGBA::WHITE);
	}

	//PLAYER 4
	if (g_theGame->m_player4Ship->m_isEnabled) {
		String p4Score = StringUtils::Stringf("PLAYER 4: %i", g_theGame->m_player4Ship->m_score);
		String p4Name = StringUtils::Stringf("LIVES: %i", g_theGame->m_player4Ship->m_remainingLives);
		m_font->DrawText2D(Vector2(1410.f, 35.f), p4Score, 0.4f, RGBA::WHITE);
		m_font->DrawText2D(Vector2(1500.f, 15.f), p4Name, 0.4f, RGBA::WHITE);
	}
}

