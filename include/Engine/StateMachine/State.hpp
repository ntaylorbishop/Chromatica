#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Console/Command.hpp"

class State {
public:
	//STRUCTORS
	State();
	State(String name);
	virtual ~State() { }

	//ENTER EXIT UPDATE RENDER
	virtual void Enter() = 0;

	virtual State* Update(float deltaSeconds) = 0;
	virtual void Render() const = 0;

	virtual bool Exit() = 0;

	

	//GETTERS SETTERS
	String GetName() const;

	//OPERATOR OVERLOADS
	bool operator==(const State& other);
	bool operator!=(const State& other);

protected:
	String m_name;
};
typedef std::map<String, State*>::iterator StateMapIterator;

//---------------------------------------------------------------------------------------------------------------------------
//INLINES
//---------------------------------------------------------------------------------------------------------------------------
inline bool State::operator==(const State& other) {
	return m_name == other.m_name;
}
inline bool State::operator!=(const State& other) {
	return !(*this == other);
}