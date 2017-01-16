#pragma once

#include "Engine/StateMachine/StateMachine.hpp"
#include "Game/MainMenuState.hpp"

class ChromaticaStateMachine : public StateMachine {
public:
	//STRUCTORS INIT
	ChromaticaStateMachine();
	~ChromaticaStateMachine();

	void Render() const;

private:
	//INHERITED:
	//State* m_currentState;
};