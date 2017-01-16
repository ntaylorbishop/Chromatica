#include "Game/Level1State.hpp"
#include "Game/Level2State.hpp"
#include "Game/Level3State.hpp"
#include "Game/Firefly.hpp"
#include "Game/TornadoBoss.hpp"
#include "Game/Bugzapper.hpp"
#include "Game/Plaguebringer.hpp"
#include "Game/Hellhound.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Level1State::Level1State()
	: State("Level1State")
	, m_levelAge(0.f)
	, m_age(0.f)
{ 
	Firefly::CreateFirefly();
}

//---------------------------------------------------------------------------------------------------------------------------
//ENTER UPDATE RENDER EXIT
//---------------------------------------------------------------------------------------------------------------------------
void Level1State::Enter() {

}

State* Level1State::Update(float deltaSeconds) {
	State* state = SwitchStates();
	if (!state) {
		UpdateLevel(deltaSeconds);
	}

	return state;
}
void Level1State::UpdateLevel(float deltaSeconds) {
	m_age += deltaSeconds;
	m_levelAge += deltaSeconds;

	if (m_age >= 1.f) {
		m_age = 0.f;
		Firefly::CreateFirefly();
	}
}

void Level1State::Render() const {

}

bool Level1State::Exit() {
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
State* Level1State::SwitchStates() {
	if (m_levelAge >= (30.f * 1.f))
	{
		return new Level2State();
	}

	return nullptr;
}