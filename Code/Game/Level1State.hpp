#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Fonts/BitmapFont.hpp"
#include "Engine/StateMachine/State.hpp"

class Level1State : public State {
public:
	//STRUCTORS
	Level1State();

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

	Texture* m_screenImage;
	float m_age;
	BitmapFont* m_squirrelFont;
	float m_levelAge;
};