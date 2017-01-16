#pragma once

#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Fonts/BitmapFont.hpp"
#include "Engine/StateMachine/State.hpp"
#include "Engine/Renderer/Fonts/Font.hpp"
#include "Engine/General/Time/Clock.hpp"

class Sprite;

class MainMenuState : public State {
public:
	//STRUCTORS
	MainMenuState();

	//ENTER UPDATE RENDER EXIT
	void Enter();

	State* Update(float deltaSeconds);
	void UpdateMainMenu(float deltaSeconds);
	void Render() const;

	bool Exit();

private:
	State* SwitchStates();

private:
	//INHERITED:
	//String m_name;
	
	bool m_whichLogo;

	Texture* m_logo1;
	Texture* m_logo2;

	Sprite* m_logoSprite;


	Font* m_font;
	Clock m_clock;

	float m_age;
};