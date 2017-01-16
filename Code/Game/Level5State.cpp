#include "Game/Level5State.hpp"
#include "Game/Bugzapper.hpp"
#include "Game/Firefly.hpp"
#include "Game/Firehound.hpp"
#include "Game/Hellhound.hpp"
#include "Game/Plaguebringer.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Level5State::Level5State()
	: State("Level5State")
	, m_age(0.f)
{ }

//---------------------------------------------------------------------------------------------------------------------------
//ENTER UPDATE RENDER EXIT
//---------------------------------------------------------------------------------------------------------------------------
void Level5State::Enter() {

}

State* Level5State::Update(float deltaSeconds) {
	State* state = SwitchStates();
	if (nullptr == state) {
		UpdateLevel(deltaSeconds);
	}

	return state;
}
void Level5State::UpdateLevel(float deltaSeconds) {
	m_age += deltaSeconds;
	if (m_age >= 1.f) {
		Bugzapper::CreateBugzapper();
		Plaguebringer::CreatePlaguebringer();
		Firehound::CreateFirehound();
		Hellhound::CreateHellhound();
		Firefly::CreateFirefly();
		Firefly::CreateFirefly();
		Bugzapper::CreateBugzapper();
		Plaguebringer::CreatePlaguebringer();
		Firehound::CreateFirehound();
		Hellhound::CreateHellhound();
		Firefly::CreateFirefly();
		Firefly::CreateFirefly();
		Bugzapper::CreateBugzapper();
		Plaguebringer::CreatePlaguebringer();
		Firehound::CreateFirehound();
		Hellhound::CreateHellhound();
		Firefly::CreateFirefly();
		Firefly::CreateFirefly();
		Firefly::CreateFirefly();
		Firefly::CreateFirefly();
		m_age = 0.f;
	}
}

void Level5State::Render() const {

}

bool Level5State::Exit() {
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
State* Level5State::SwitchStates() {
	/*
	if (g_theInputSystem->GetKeyDown(VK_ESCAPE)) {
	g_thePauseMenu->Toggle();
	}

	if (g_thePauseMenu->IsExiting()) {
	return new LevelSelectState();
	}

	if (g_theWorld->m_exiting) {
	return new ExitGameState();
	}
	*/

	return nullptr;
}