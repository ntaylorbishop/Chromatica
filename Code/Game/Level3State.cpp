#include "Game/Level3State.hpp"
#include "Game/Level4State.hpp"
#include "Game/TornadoBoss.hpp"
#include "Game/Firefly.hpp"
#include "Game/Firehound.hpp"
#include "Game/Bugzapper.hpp"
#include "Game/Hellhound.hpp"
#include "Game/Plaguebringer.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Level3State::Level3State()
	: State("Level3State")
	, m_age(0.f)
	, m_levelAge(0.f)
{ 
	Firefly::CreateFirefly();
	Firefly::CreateFirefly();
	Firefly::CreateFirefly();
	Firehound::CreateFirehound();
	Firehound::CreateFirehound();
	Firehound::CreateFirehound();
	TornadoBoss::CreateTornadoBoss();
}

//---------------------------------------------------------------------------------------------------------------------------
//ENTER UPDATE RENDER EXIT
//---------------------------------------------------------------------------------------------------------------------------
void Level3State::Enter() {

}

State* Level3State::Update(float deltaSeconds) {
	State* state = SwitchStates();
	if (nullptr == state) {
		UpdateLevel(deltaSeconds);
	}

	return state;
}
void Level3State::UpdateLevel(float deltaSeconds) {
	m_age += deltaSeconds;
	m_levelAge += deltaSeconds;

	if (m_age >= 1.f) {
		Firefly::CreateFirefly();
		Firehound::CreateFirehound();
		Hellhound::CreateHellhound();
		Hellhound::CreateHellhound();
		m_age = 0.f;
	}
}

void Level3State::Render() const {

}

bool Level3State::Exit() {
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
State* Level3State::SwitchStates() {
	
	if (m_levelAge >= (60.f * 1.f)) {
		return new Level4State();
	}
	return nullptr;
}