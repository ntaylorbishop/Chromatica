#include "Game/ChromaticaStateMachine.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS INITIALIZATION
//---------------------------------------------------------------------------------------------------------------------------
ChromaticaStateMachine::ChromaticaStateMachine() {
	m_currentState = new MainMenuState();
}
ChromaticaStateMachine::~ChromaticaStateMachine() {
	delete m_currentState;
	m_currentState = nullptr;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void ChromaticaStateMachine::Render() const {
	m_currentState->Render();
}