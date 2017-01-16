#include "Game/Level2State.hpp"
#include "Game/NightmareBoss.hpp"
#include "Game/Firehound.hpp"
#include "Game/Firefly.hpp"
#include "Game/Level3State.hpp"
#include "Game/TornadoBoss.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Level2State::Level2State()
	: State("Level2State")
	, m_age(0.f)
	, m_levelAge(0.f)
{ 
	NightmareBoss::CreateNightmareBoss();
}

//---------------------------------------------------------------------------------------------------------------------------
//ENTER UPDATE RENDER EXIT
//---------------------------------------------------------------------------------------------------------------------------
void Level2State::Enter() {

}

State* Level2State::Update(float deltaSeconds) {
	State* state = SwitchStates();
	if (nullptr == state) {
		UpdateLevel(deltaSeconds);
	}

	return state;
}
void Level2State::UpdateLevel(float deltaSeconds) {
	m_age += deltaSeconds;
	m_levelAge += deltaSeconds;

	if (m_age >= SPAWN_RATE) {
		m_age = 0.f;

		if (m_levelAge >= 30.f) {
			Firehound::CreateFirehound();
			Firefly::CreateFirefly();
			Firehound::CreateFirehound();
			Firefly::CreateFirefly();
			Firehound::CreateFirehound();
			Firefly::CreateFirefly();
			return;
		}

		int which = RandInt(0, 1);

		if (which == 0)
			Firehound::CreateFirehound();
		else {
			Firehound::CreateFirehound();
			Firefly::CreateFirefly();
		}
	}
}

void Level2State::Render() const {

}

bool Level2State::Exit() {
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
State* Level2State::SwitchStates() {

	if (m_levelAge >= (60.f * 1.f)) {
		return new Level3State();
	}

	return nullptr;
}