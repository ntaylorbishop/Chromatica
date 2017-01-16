#include "Game/Level4State.hpp"
#include "Game/Bugzapper.hpp"
#include "Game/Plaguebringer.hpp"
#include "Game/Level5State.hpp"
#include "Game/TornadoBoss.hpp"
#include "Game/Firefly.hpp"
#include "Game/Firehound.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Level4State::Level4State()
	: State("Level4State")
	, m_age(0.f)
	, m_levelAge(0.f)
{ 
}

//---------------------------------------------------------------------------------------------------------------------------
//ENTER UPDATE RENDER EXIT
//---------------------------------------------------------------------------------------------------------------------------
void Level4State::Enter() {

}

State* Level4State::Update(float deltaSeconds) {
	State* state = SwitchStates();
	if (nullptr == state) {
		UpdateLevel(deltaSeconds);
	}

	return state;
}
void Level4State::UpdateLevel(float deltaSeconds) {
	m_age += deltaSeconds;
	m_levelAge += deltaSeconds;

	if (m_age >= 0.8f) {
		Firefly::CreateFirefly();
		Firehound::CreateFirehound();
		Firefly::CreateFirefly();
		Firehound::CreateFirehound();
		Bugzapper::CreateBugzapper();
		Plaguebringer::CreatePlaguebringer();
		m_age = 0.f;
	}
}

void Level4State::Render() const {

}

bool Level4State::Exit() {
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
State* Level4State::SwitchStates() {

	if (m_levelAge >= (60.f * 1.f)) {
		return new Level5State();
	}

	return nullptr;
}