#pragma once

#include <vector>
#include <string>
#include "Engine/General/Console/Console.hpp"
#include "Engine/General/Input/InputSystem.hpp"
#include "Engine/Renderer/Renderer/TheDebugRenderer.hpp"
#include "Engine/General/Logger/TheLogger.hpp"
#include "Engine/General/UI/UISystem.hpp"
#include "Engine/Tools/FBX.hpp"
#include "Engine/Renderer/Fonts/BitmapFont.hpp"
#include "Engine/General/Core/TheMemoryManager.hpp"
#include "Engine/General/Time/Clock.hpp"
#include "Engine/General/JobSystem/JobSystem.hpp"

#pragma warning(push, 1)
#include "ThirdParty/FastDelegate.h"
#pragma warning(pop)
using namespace fastdelegate;

typedef void(*console_commmand_cb)(Command&);
typedef FastDelegate1<float> UpdateDelegate;

class GameEngine;
extern GameEngine* g_theApparatusEngine;

class GameEngine {
public:
	//STRUCTORS AND INITIALIZATION
	GameEngine();
	~GameEngine();
	void Initialize();
	void Shutdown();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	void RenderDebugRenderer();
	void RenderConsole();
	void RenderUI() const;

	//CONSOLE API
	void BindKeyToConsole(unsigned char asKey);
	void PrintOutputToConsole(std::string output, eConsoleColor color);
	void PrintMonospaceOutputToConsole(std::string output, eConsoleColor color);
	void PrintDebugOutputToConsole(std::string output, eConsoleColor color);

	void SendInputToConsole(unsigned char asKey);
	void RegisterCommandToConsole(std::string name, std::string tooltip, console_command_cb cb);
	void RunConsoleCommand(std::string commandLine);
	void ClearConsole();

	bool IsConsoleOpen();

	float GetWidthOfStringOnConsole(const String& str);

	//INPUT
	void ProcessInput(unsigned char asKey, bool isDown);
	bool GetKeyDown(unsigned char asKey);
	bool GetKey(unsigned char asKey);

	void SetMouseWheelDelta(short wheelDelta);
	bool GetMouseWheelUp();
	bool GetMouseWheelDown();

	//FOR ENGINE USE ONLY
	unsigned char GetKeyBindForConsole();

	//TEXT RENDERING
	void DrawTextAtLocation(const Vector2& location, const String& str, float scale, const RGBA& color);
	float GetDefaultTextLineHeight() const { return m_font->GetLineHeight(); }

	//UPDATE REGISTRATION
	void RegisterUpdateCallback(UpdateDelegate updateFunc);
	void UnregisterUpdateCallback(UpdateDelegate updateFunc);

	std::vector<std::string> m_commandList;

	//CLOCK
	Clock* GetEngineClock() const { return m_engineClock; }

private:
	void ToggleConsole();

private:
	unsigned char m_asKeyForConsole;

	//ENTITY SYSTEM
	bool m_entitySystemEnabled;

	//INPUT
	bool m_isKeyDown[NUM_KEYS];
	int m_mouseWheelUpDelta;
	int m_mouseWheelDownDelta;

	Font* m_font;
	Console* m_developerConsole;

	std::vector<UpdateDelegate> m_updateFuncsToCall;
	Clock* m_engineClock;
};

void Help(Command& args);
void FbxListScene(Command& args);

#if MEMORY_TRACKING == 1
void ShowMemoryDebugWindow(Command& args);
#elif MEMORY_TRACKING == 2
void ShowMemoryDebugWindow(Command& args);
void MemFlushCommand(Command& args);
#endif