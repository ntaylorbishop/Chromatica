#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/StateMachine/State.hpp"

class StateMachine {
public:
	//STRUCTORS INITIALIZATION
	StateMachine();

	//UPDATE
	void Update(float deltaSeconds);

protected:
	State* m_currentState;
};