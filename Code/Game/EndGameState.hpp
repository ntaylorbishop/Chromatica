#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Fonts/BitmapFont.hpp"
#include "Engine/StateMachine/State.hpp"

class PlayerShip;
class Font;

struct PlayerNumAndScore {
	int m_playerNum;
	int m_playerScore;
};

class EndGameState : public State {
public:
	//STRUCTORS
	EndGameState();

	//ENTER UPDATE RENDER EXIT
	void Enter();

	State* Update(float deltaSeconds);
	void UpdateEndGameState(float deltaSeconds);

	void Render() const;

	bool Exit();


private:
	State* SwitchStates();

private:
	//INHERITED:
	//String m_name;

	PlayerNumAndScore m_scores[4];

	float m_age;
	Font* m_font;
	Texture* m_gameOverScreen;
};

int ScoreComparator(const void * score1, const void * score2);