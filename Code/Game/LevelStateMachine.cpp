#include "Game/LevelStateMachine.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS INITIALIZATION
//---------------------------------------------------------------------------------------------------------------------------
LevelStateMachine::LevelStateMachine() {
	m_currentState = new Level1State();
}
LevelStateMachine::~LevelStateMachine() {
	//delete m_currentState;
	//m_currentState = nullptr;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void LevelStateMachine::Render() const {
	m_currentState->Render();
}