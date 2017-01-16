#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Fonts/BitmapFont.hpp"
#include "Engine/StateMachine/State.hpp"
#include "Game/PlayerShip.hpp"
#include "Game/LevelStateMachine.hpp"

class PlayingGameState : public State {
public:
	//STRUCTORS
	PlayingGameState();
	~PlayingGameState();

	//ENTER UPDATE RENDER EXIT
	void Enter();

	State* Update(float deltaSeconds);
	void UpdatePlayingGame(float deltaSeconds);

	void Render() const;

	bool Exit();

private:
	State* SwitchStates();

private:
	//INHERITED:
	//String m_name;

	bool m_isStillAlive;

	float m_age;
	LevelStateMachine m_levelStateMachine;
};