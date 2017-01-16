#pragma once

#include "Engine/General/Core/GameEngine.hpp"
#include "Engine/General/Core/WindowHandler.hpp"
#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Fonts/Font.hpp"

class TheUI;
extern TheUI* g_theUI;

class TheUI {
public:
	//STRUCTORS
	TheUI();
	~TheUI();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	Font* m_font;
	BitmapFont* m_squirrelFont;
	bool m_isEnabled;

private:
	void RenderDebugText() const;
	void RenderScores() const;
};