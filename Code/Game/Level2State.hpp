#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Fonts/BitmapFont.hpp"
#include "Engine/StateMachine/State.hpp"

const float SPAWN_RATE = 1.5f;

class Level2State : public State {
public:
	//STRUCTORS
	Level2State();

	//ENTER UPDATE RENDER EXIT
	void Enter();

	State* Update(float deltaSeconds);
	void UpdateLevel(float deltaSeconds);

	void Render() const;

	bool Exit();

private:
	State* SwitchStates();

private:
	//INHERITED:
	//String m_name;

	float m_levelAge;
	Texture* m_screenImage;
	float m_age;
	BitmapFont* m_squirrelFont;
};