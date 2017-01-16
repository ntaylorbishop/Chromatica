#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <gl/gl.h>
#include <math.h>
#include <cassert>
#include <crtdbg.h>
#pragma comment( lib, "opengl32" )

#include "Engine/General/Core/GameEngine.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"
#include "Engine/Renderer/Material/Material.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"
#include "Engine/General/Time/Time.hpp"
#include "Engine/Renderer/Framebuffer.hpp"
#include "Engine/Renderer/General/Texture.hpp"
#include "Engine/General/Core/WindowHandler.hpp"
#include "Game/TheUI.hpp"
#include "Game/TheApp.hpp"
#include "Game/TheGame.hpp"
#include "Game/MaterialManager.hpp"
#include "Engine/General/Profiler/Profiler.hpp"

#define UNUSED(x) (void)(x);

//---------------------------------------------------------------------------------------------------------------------------
//WINDOW CREATION
//---------------------------------------------------------------------------------------------------------------------------
#if IS_WINDOWED
	const int OFFSET_FROM_WINDOWS_DESKTOP = 10;
	const int WINDOW_PHYSICAL_WIDTH = 1600;
	const int WINDOW_PHYSICAL_HEIGHT = 900;
	const double VIEW_RIGHT = 1600.0;
#else
	const int OFFSET_FROM_WINDOWS_DESKTOP = 0;
	const int WINDOW_PHYSICAL_WIDTH = 1920;
	const int WINDOW_PHYSICAL_HEIGHT = 1080;
	const double VIEW_RIGHT = 1920.0;
#endif

const double VIEW_LEFT = 0.0;
const double VIEW_BOTTOM = 0.0;
const double VIEW_TOP = VIEW_RIGHT * static_cast<double>(WINDOW_PHYSICAL_HEIGHT) / static_cast<double>(WINDOW_PHYSICAL_WIDTH);

HWND g_hWnd = nullptr;
HDC g_displayDeviceContext = nullptr;
HGLRC g_openGLRenderingContext = nullptr;
const char* APP_NAME = "Chromatica";


//---------------------------------------------------------------------------------------------------------------------------
//INPUT CALLBACK
//---------------------------------------------------------------------------------------------------------------------------
LRESULT CALLBACK WindowsMessageHandlingProcedure(HWND windowHandle, UINT wmMessageCode, WPARAM wParam, LPARAM lParam) {
	unsigned char asKey = (unsigned char)wParam;
	switch (wmMessageCode) {
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_QUIT:
		g_theInputSystem->Quitting(true);
		return 0;
	case WM_KEYDOWN:
		g_theInputSystem->SetKeyDownStatus(asKey, true);
		g_theApparatusEngine->ProcessInput(asKey, true);

		if (asKey == VK_ESCAPE) {
			if (!g_theApparatusEngine->IsConsoleOpen()) {
				g_theInputSystem->Quitting(true);
				return 0;
			}
		}
		break;
	case WM_CHAR:
		g_theApparatusEngine->SendInputToConsole(asKey);
		break;

	case WM_KEYUP:
		g_theInputSystem->SetKeyDownStatus(asKey, false);
		g_theApparatusEngine->ProcessInput(asKey, false);

		break;
	case WM_SETFOCUS:
		if(g_theApp)
			g_theApp->OnGainedFocus();
		break;
	case WM_KILLFOCUS:
		if (g_theApp)
			g_theApp->OnLostFocus();
		break;
	case WM_LBUTTONDOWN:
		g_theInputSystem->SetMouseBtnDown(MOUSE_LEFT, true);
		break;
	case WM_LBUTTONUP:
		g_theInputSystem->SetMouseBtnDown(MOUSE_LEFT, false);
		break;
	case WM_MBUTTONDOWN:
		g_theInputSystem->SetMouseBtnDown(MOUSE_MIDDLE, true);
		break;
	case WM_MBUTTONUP:
		g_theInputSystem->SetMouseBtnDown(MOUSE_MIDDLE, false);
		break;
	case WM_RBUTTONDOWN:
		g_theInputSystem->SetMouseBtnDown(MOUSE_RIGHT, true);
		break;
	case WM_RBUTTONUP:
		g_theInputSystem->SetMouseBtnDown(MOUSE_RIGHT, false);
		break;
	case WM_MOUSEWHEEL:
		g_theInputSystem->SetMouseWheelDelta(GET_WHEEL_DELTA_WPARAM(wParam));
		g_theApparatusEngine->SetMouseWheelDelta(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	}

	return DefWindowProc(windowHandle, wmMessageCode, wParam, lParam);
}

//---------------------------------------------------------------------------------------------------------------------------
//CREATE OPENGL CONTEXT AND WINDOW
//---------------------------------------------------------------------------------------------------------------------------
void CreateOpenGLContextAndWindow(HINSTANCE applicationInstanceHandle) {
	// Define a window class
	WNDCLASSEX windowClassDescription;
	memset(&windowClassDescription, 0, sizeof(windowClassDescription));
	windowClassDescription.cbSize = sizeof(windowClassDescription);
	windowClassDescription.style = CS_OWNDC; // Redraw on move, request own Display Context
	windowClassDescription.lpfnWndProc = static_cast<WNDPROC>(WindowsMessageHandlingProcedure); // Assign a win32 message-handling function
	windowClassDescription.hInstance = GetModuleHandle(NULL);
	windowClassDescription.hIcon = NULL;
	windowClassDescription.hCursor = NULL;
	windowClassDescription.lpszClassName = TEXT("Simple Window Class");
	RegisterClassEx(&windowClassDescription);

	#if IS_WINDOWED
		const DWORD windowStyleFlags = WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_SYSMENU | WS_OVERLAPPED;
		const DWORD windowStyleExFlags = WS_EX_APPWINDOW;
	#else
		const DWORD windowStyleFlags = WS_POPUP;
		const DWORD windowStyleExFlags = WS_EX_APPWINDOW;
	#endif

	RECT desktopRect;
	HWND desktopWindowHandle = GetDesktopWindow();
	GetClientRect(desktopWindowHandle, &desktopRect);

	RECT windowRect = { OFFSET_FROM_WINDOWS_DESKTOP, OFFSET_FROM_WINDOWS_DESKTOP, OFFSET_FROM_WINDOWS_DESKTOP + WINDOW_PHYSICAL_WIDTH, OFFSET_FROM_WINDOWS_DESKTOP + WINDOW_PHYSICAL_HEIGHT };
	AdjustWindowRectEx(&windowRect, windowStyleFlags, FALSE, windowStyleExFlags);

	WCHAR windowTitle[1024];
	MultiByteToWideChar(GetACP(), 0, APP_NAME, -1, windowTitle, sizeof(windowTitle) / sizeof(windowTitle[0]));
	g_hWnd = CreateWindowEx(
		windowStyleExFlags,
		windowClassDescription.lpszClassName,
		windowTitle,
		windowStyleFlags,
		windowRect.left,
		windowRect.top,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		applicationInstanceHandle,
		NULL
	);

	g_theWindowHandler->RegisterMainWindow(g_hWnd);

	ShowWindow(g_hWnd, SW_SHOW);
	SetForegroundWindow(g_hWnd);
	SetFocus(g_hWnd);

	g_displayDeviceContext = GetDC(g_hWnd);

	HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(cursor);

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	memset(&pixelFormatDescriptor, 0, sizeof(pixelFormatDescriptor));
	pixelFormatDescriptor.nSize = sizeof(pixelFormatDescriptor);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 24;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.cAccumBits = 0;
	pixelFormatDescriptor.cStencilBits = 8;

	int pixelFormatCode = ChoosePixelFormat(g_displayDeviceContext, &pixelFormatDescriptor);
	SetPixelFormat(g_displayDeviceContext, pixelFormatCode, &pixelFormatDescriptor);
	g_openGLRenderingContext = wglCreateContext(g_displayDeviceContext);
	wglMakeCurrent(g_displayDeviceContext, g_openGLRenderingContext);

	//Set some standard 2D settings up. TheGame will change it if it wants
	g_theRenderer->EnableBlending();
	g_theRenderer->BlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	g_theRenderer->LineWidth(2.f);
	g_theRenderer->EnableLineSmoothing();
	//g_theRenderer->EnableGLAlphaFunc(0.1f);
}


//-----------Main game Loop--------------------------------
void RunMessagePump() {
	MSG queuedMessage;
	for (;;)
	{
		const BOOL wasMessagePresent = PeekMessage(&queuedMessage, NULL, 0, 0, PM_REMOVE);
		if (!wasMessagePresent)
		{
			break;
		}

		TranslateMessage(&queuedMessage);
		DispatchMessage(&queuedMessage);
	}
}
void Update() {
	static double s_timeLastFrameBegan = Time::GetCurrentTimeSeconds();

	double timeThisFrameBegan = Time::GetCurrentTimeSeconds();
	float deltaSeconds = static_cast<float>(timeThisFrameBegan - s_timeLastFrameBegan); //In seconds

	s_timeLastFrameBegan = timeThisFrameBegan;


	g_theApparatusEngine->Update(deltaSeconds);
	g_theGame->Update(deltaSeconds);
	g_theUI->Update(deltaSeconds);
}
void Render() {
	g_theGame->Render();
	g_theApparatusEngine->RenderDebugRenderer();

	g_theUI->Render();
	g_theApparatusEngine->RenderUI();
	g_theApparatusEngine->Render();
	g_theApparatusEngine->RenderConsole();

	SwapBuffers(g_displayDeviceContext);
}
void RunFrame() {
	Profiler::MarkFrame();
	RunMessagePump();
	Update();
	Render();
}

//-----------Initialization and shutdown-------------------
void InitializeEngine() {
	g_theApparatusEngine = new GameEngine();
	g_theApparatusEngine->Initialize();
	Profiler::Startup();
}
void InitializeGame(HINSTANCE applicationInstanceHandle) {
	g_theApp = new TheApp(ScreenCoords(1600, 900));
	g_theWindowHandler = new WindowHandler();

	SetProcessDPIAware();
	CreateOpenGLContextAndWindow(applicationInstanceHandle);


	InitializeEngine();

	g_theUI = new TheUI();
	g_theGame = new TheGame();
}
void Shutdown() {

	g_theApparatusEngine->Shutdown();
	delete g_theGame;
	g_theGame = nullptr;
	delete g_theUI;
	g_theUI = nullptr;
	delete g_theApparatusEngine;
	g_theApparatusEngine = nullptr;
	delete g_theApp;
	g_theApp = nullptr;
	delete g_theMaterialManager;
	g_theMaterialManager = nullptr;

	delete g_theWindowHandler;
	g_theWindowHandler = nullptr;
}

//Driver
int WINAPI WinMain(HINSTANCE applicationInstanceHandle, HINSTANCE, LPSTR commandLineString, int) {
	UNUSED(commandLineString);

	#if MEMORY_TRACKING != 0
	MemoryAnalyticsStartup();
	#else
	CallstackSystemInit();
	#endif


	InitializeGame(applicationInstanceHandle);

	while (!g_theInputSystem->HasQuit())
		RunFrame();

	Shutdown();

	Profiler::Shutdown();

	#if MEMORY_TRACKING != 0
	MemoryAnalyticsShutdown();
	#else
	CallstackSystemDeinit();
	#endif
	return 0;
}