#pragma once

#include <map>
#include <vector>
#include <string>
#include <functional>
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/General/RGBA.hpp"
#include "Engine/Renderer/Fonts/BitmapFont.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/General/Console/Cursor.hpp"
#include "Engine/General/Input/InputSystem.hpp"
#include "Engine/Renderer/Fonts/Font.hpp"
#include "Engine/General/Console/Command.hpp"

typedef void(*console_command_cb)(Command&);

enum eConsoleColor {
	CONSOLE_WARNING = 0,
	CONSOLE_VERIFY,
	CONSOLE_DEBUG,
	CONSOLE_NORMAL
};

const uint MAX_PREV_INPUTS = 100;


class Console {
public:
	//STRUCTORS
	Console();
	~Console();

	//API COMMANDS
	void RegisterCommand(std::string name, std::string tooltip, console_command_cb);
	void RunCommand(std::string commandLine);

	void ShowConsole();
	void HideConsole();
	bool IsOpen();

	void PrintOutput(eConsoleColor cColor, std::string output, bool isProportional);
	void PrintDebugOutput(eConsoleColor cColor, std::string output);
	void RegisterCharacterInput(unsigned char asKey);

	void ClearConsole();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	Font* m_newConsoleFont;
private:
	void UpdatePrevInputIndices();
	void ChangeCurrSelectedLine(int whatToAddToIdx);

	void RenderCommandLine() const;
	void RenderCurrentInput() const;
	void RenderPreviousInputs() const;

	//Console settings
	bool m_isActive;
	Vector2 m_screenSizeForConsole;
	Cursor* m_cursor;
	BitmapFont* m_consoleFont;
	float m_consoleScale;
	
	//Command line
	std::vector<unsigned char> m_currentInput;
	std::vector<std::pair<bool, std::pair<std::string, RGBA>>> m_prevInputs;
	Glyph* m_currGlyphSelected;
	int m_idxOfCurrGlyphSelected;
	int m_numWindowLines;
	int m_prevInputStartIdx;
	int m_prevInputEndIdx;
	int m_idxOfLastLineShown;
	int m_currentLineSelected;
	std::vector<unsigned char> m_currentInputHidden;
	std::vector<std::string> m_prevCommands;

	float m_age;
	
	//Commands
	static std::map<size_t, console_command_cb, std::less<size_t>, UntrackedAllocator<std::pair<size_t, console_command_cb>>> s_commands;

};

typedef std::pair<std::string, std::string> StringPair;

//COMMANDS
void ClearConsoleCommand(Command& args);
void QuitApplication(Command& args);