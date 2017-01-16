#pragma once

#include "Engine/StateMachine/StateMachine.hpp"
#include "Game/Level1State.hpp"

class LevelStateMachine : public StateMachine {
public:
	//STRUCTORS INIT
	LevelStateMachine();
	~LevelStateMachine();

	void Render() const;

private:
	//INHERITED:
	//State* m_currentState;
};