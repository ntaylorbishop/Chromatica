#pragma once

#include <fstream>
#include <iostream>

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Core/Structures/Thread.hpp"
#include "Engine/General/Core/Structures/TSQueue.hpp"
#include "Engine/General/Utils/StringUtils.hpp"
#include "Engine/General/Core/Structures/MutexLock.hpp"

class TheLogger;
extern TheLogger* g_theLogger;

typedef void(WriteFunctionCallback)(const String&);

//---------------------------------------------------------------------------------------------------------------------------
//ENUMS, STRUCTS, CONSTS
//---------------------------------------------------------------------------------------------------------------------------
enum eLogLevel {
	LOG_NONE = 0,
	LOG_SEVERE,
	LOG_RECOVERABLE,
	LOG_DEFAULT,
	LOG_ALL
};

enum eListMode {
	LOG_WHITELIST = 0,
	LOG_BLACKLIST
};

struct LogMessage {
	std::string msg;
	std::string tag;
	eLogLevel logLvl;
	bool printCallstack;
};

const char LOG_FILE_PATH[] = "Data/Logs/";
const char LOG_FILE_NAME[] = "debug";

//---------------------------------------------------------------------------------------------------------------------------
//LOGGER CLASS
//---------------------------------------------------------------------------------------------------------------------------
class TheLogger {
public:
	TheLogger();
	~TheLogger();
	void Initialize();

	//LOGGER THREAD
	void HandleMessage(LogMessage msgToProcess);
	void FlushRemainingMessages();

	//MAIN THREAD

	TSQueue<LogMessage> m_messageBuffer;
	MutexLock m_listedTagsLock;
	std::vector<std::string> m_listedTags;
	eListMode m_logListMode;
	std::fstream m_file;
	String m_fileName;

private:

	Thread m_thread;
	std::fstream file;
	std::vector<WriteFunctionCallback*> m_writeCallbacks;

	eLogLevel m_logLevel;
};

//---------------------------------------------------------------------------------------------------------------------------
//OUTSIDE FUNCS
//---------------------------------------------------------------------------------------------------------------------------
void Run();

void LogPrintf(const char* messageFormat, const char* tag, eLogLevel logLevel, ...);
void LogPrintfWithCallstack(const char* messageFormat, const char* tag, eLogLevel logLevel, ...);

void LogEnable(const char* tag);
void LogDisable(const char* tag);
void LogDisableAll();

void WriteToOutputWindow(const String& output);
void WriteToDevConsole(const String& output);
void WriteToFile(const String& output);