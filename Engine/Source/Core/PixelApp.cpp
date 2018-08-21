#include "Include/Core/PixelApp.h"

#include "Include/PixelError.h"
#include "Include/Core/SceneManager.h"
#include "Include/Core/SelectionService.h"
#include "Include/Core/LogService.h"
#include "Include/Core/UserInputService.h"
#include "Include/Core/ContentProvider.h"
#include "Include/Core/SoundService.h"
#include "Include/Core/EventManager.h"

#include "Include/Graphics/RenderService.h"
#include "Include/Graphics/GuiService.h"

#include "Include/Physics/PhysicsService.h"

#include "Include/Network/HttpService.h"

#undef CreateWindow

PIXEL_DECLARE_SINGLETON(Pixel::App);

Pixel::App::App(Pixel::WindowSubsystem subsystem) : _subsystem(subsystem)
{
	Pixel::LogService::Singleton();
	Pixel::StandardOut::Singleton();

	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::App);

	//Create singleton services
	new Pixel::EventManager();
	new Pixel::HttpService();
	new Pixel::ContentProvider();
	new Pixel::GuiService();
	new Pixel::SoundService();
	new Pixel::UserInputService();
	new Pixel::SceneManager();
	new Pixel::PhysicsService();
	new Pixel::RenderService();
	new Pixel::SelectionService();
}

Pixel::App::~App()
{
	Close();

	//Free singleton services
	delete Pixel::SelectionService::Singleton();
	delete Pixel::RenderService::Singleton();
	delete Pixel::PhysicsService::Singleton();
	delete Pixel::SceneManager::Singleton();
	delete Pixel::UserInputService::Singleton();
	delete Pixel::SoundService::Singleton();
	delete Pixel::GuiService::Singleton();
	delete Pixel::ContentProvider::Singleton();
	delete Pixel::HttpService::Singleton();
	delete Pixel::EventManager::Singleton();

	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::App);

	Pixel::LogService::Singleton()->UploadLogs();
}

void Pixel::App::CreateWindow(std::string title, int width, int height)
{
	if (!IsSDL())
	{
		PixelError("App::CreateWindow() - This function can only be used with the SDL window subsystem");
		return;
	}

	if (_hasWindow || _window != nullptr)
	{
		PixelError("App::CreateWindow() - A window is already created");
		return;
	}

	_windowTitle = title;
	_windowWidth = width;
	_windowHeight = height;

	Pixel::RenderService::Singleton()->SetViewport(width, height);

	//Initialize SDL GL attributes (must do before window creation)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
	//Initialize SDL video subsystem (if it isn't already)
	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		if (SDL_Init(SDL_INIT_VIDEO) == 0)
		{
			Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info, "App::CreateWindow() - SDL video subsystem initialized");
		}
		else
		{
			PixelFatalError("SDL video subsystem initialization failed");
		}
	}
	//Create SDL window
	_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN
	);
	if (_window != NULL)
	{
		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info, "App::CreateWindow() - SDL window created");
		_hasWindow = true;
	}
	else
	{
		PixelFatalError("SDL window creation failed");
	}

	//Initialize GLContext
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext != NULL)
	{
		Pixel::RenderService::Singleton()->SetGLContext(glContext);
		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info, "App::CreateWindow() - OpenGL context created");
	}
	else
	{
		PixelFatalError("OpenGL context creation failed");
	}

	//Obtain SDL system info
	SDL_VERSION(&_SDLSysInfo.version);
	if (SDL_GetWindowWMInfo(_window, &_SDLSysInfo) == SDL_FALSE)
	{
		PixelFatalError("Failed to initialize SDL window system information");
	}
}

void Pixel::App::DestroyWindow()
{
	if (!IsSDL())
	{
		PixelError("App::DestroyWindow() - This function can only be used with the SDL window subsystem");
		return;
	}

	if (_window == nullptr)
	{
		PixelError("App::DestroyWindow() - Cannot destroy window because no window exists");
		return;
	}

	SDL_DestroyWindow(_window);
	_hasWindow = false;
	_window = nullptr;
}

void Pixel::App::SetWxWidgetsWindow(wxWindow* window)
{
	window->GetSize(&_windowWidth, &_windowHeight);
	_wxWindow = window;
}

void Pixel::App::ProcessEvents()
{
	if (_closeRequested)
		return;

	Pixel::UserInputService::Singleton()->Update();
}

void Pixel::App::StepPhysics()
{
	if (_closeRequested)
		return;

	static Pixel::PhysicsService* physicsService = Pixel::PhysicsService::Singleton();
	static Pixel::RenderService* renderService = Pixel::RenderService::Singleton();

	//Simulate game
	physicsService->TimeFrame();
	physicsService->SimulateGameObjects();
	physicsService->SimulateSystemObjects();

	//Update camera
	renderService->GetCurrentCamera()->Update(physicsService->GetLastPhysicsFrameDelta());
}

void Pixel::App::Render()
{
	if (_closeRequested)
		return;

	if (_window == nullptr && IsSDL())
	{
		PixelFatalError("App::Render() - Cannot render because no window exists");
		return;
	}

	static Pixel::RenderService* renderService = Pixel::RenderService::Singleton();

	static bool hasInitialized = false;
	if (!hasInitialized)
	{
		if (!renderService->IsInitialized())
			renderService->Initialize();
		hasInitialized = true;
	}

	renderService->SetupFrame();
	renderService->Clear();

	renderService->RenderWorldObjects();
	renderService->RenderSystemObjects();

	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 1.0f, 0.0f);

	renderService->RenderScreenGuis();
	if (_debugGuiEnabled)
	{
		renderService->RenderSystemGuis();
	}

	if (IsSDL())
		SDL_GL_SwapWindow(_window);
}

void Pixel::App::UpdateSound()
{
	if (_closeRequested)
		return;

	Pixel::SoundService::Singleton()->Update();
}

void Pixel::App::StepGame()
{
	ProcessEvents();
	StepPhysics();
	Render();
	UpdateSound();
}

void Pixel::App::StartGameLoop()
{
	_autoGameLoop = true;
	while (!_closeRequested && _autoGameLoop)
	{
		StepGame();
	}
}

void Pixel::App::StopGameLoop()
{
	_autoGameLoop = false;
}

void Pixel::App::Close()
{
	_closeRequested = true;
	StopGameLoop();
	if (IsSDL())
	{
		if (_hasWindow)
			DestroyWindow();

		SDL_Quit();
	}
}

void Pixel::App::SetWindowTitle(std::string title)
{
	if (!IsSDL())
	{
		PixelError("App::SetWindowTitle() - This function can only be used with the SDL window subsystem");
		return;
	}

	if (_window == nullptr)
	{
		PixelError("App::SetWindowTitle() - Cannot set window title because no window exists");
		return;
	}

	SDL_SetWindowTitle(_window, title.c_str());
	_windowTitle = title;
}

void Pixel::App::SetWindowSize(int width, int height)
{
	if (!IsSDL())
	{
		PixelError("App::SetWindowSize() - This function can only be used with the SDL window subsystem");
		return;
	}

	if (_window == nullptr)
	{
		PixelError("App::SetWindowSize() - Cannot set window size because no window exists");
		return;
	}

	_windowWidth = width;
	_windowHeight = height;
	SDL_SetWindowSize(_window, width, height);
}

void Pixel::App::SetWindowWidth(int value)
{
	if (!IsSDL())
	{
		PixelError("App::SetWindowWidth() - This function can only be used with the SDL window subsystem");
		return;
	}

	if (_window == nullptr)
	{
		PixelError("App::SetWindowWidth() - Cannot set window width because no window exists"); 
		return;
	}

	SetWindowSize(value, _windowHeight);
}

void Pixel::App::SetWindowHeight(int value)
{
	if (!IsSDL())
	{
		PixelError("App::SetWindowHeight() - This function can only be used with the SDL window subsystem");
		return;
	}

	if (_window == nullptr)
	{
		PixelError("App::SetWindowHeight() - Cannot set window height because no window exists");
		return;
	}

	SetWindowSize(_windowWidth, value);
}

void Pixel::App::SetWindowVisible(bool value)
{
	if (!IsSDL())
	{
		PixelError("App::SetWindowVisible() - This function can only be used with the SDL window subsystem");
		return;
	}

	if (_window == nullptr)
	{
		PixelError("App::SetWindowVisible() - Cannot set window visibility because no window exists");
		return;
	}

	if (value)
	{
		SDL_ShowWindow(_window);
	}
	else
	{
		SDL_HideWindow(_window);
	}
	_isWindowVisible = value;
}

void Pixel::App::SetDebugGuiEnabled(bool enabled)
{
	_debugGuiEnabled = enabled;
}

int Pixel::App::GetWindowPositionX() const
{
	if (!IsSDL())
	{
		PixelError("App::GetWindowPositionX() - This function can only be used with the SDL window subsystem");
		return 0;
	}

	if (_window == nullptr)
	{
		PixelError("App::GetWindowPositionX() - Cannot get window position because no window exists");
		return 0;
	}

	int value;
	SDL_GetWindowPosition(_window, &value, nullptr);
	return value;
}

int Pixel::App::GetWindowPositionY() const
{
	if (!IsSDL())
	{
		PixelError("App::GetWindowPositionY() - This function can only be used with the SDL window subsystem");
		return 0;
	}

	if (_window == nullptr)
	{
		PixelError("App::GetWindowPositionY() - Cannot get window position because no window exists");
		return 0;
	}

	int value;
	SDL_GetWindowPosition(_window, nullptr, &value);
	return value;
}

Pixel::Type::Position Pixel::App::GetWindowPosition() const
{
	if (!IsSDL())
	{
		PixelError("App::GetWindowPosition() - This function can only be used with the SDL window subsystem");
		return Pixel::Type::Position(0.0);
	}

	if (_window == nullptr)
	{
		PixelError("App::GetWindowPosition() - Cannot get window position because no window exists");
		return Pixel::Type::Position(0.0);
	}

	int posX;
	int posY;
	SDL_GetWindowPosition(_window, &posX, &posY);
	Pixel::Type::Position position(posX, posY);
	return position;
}

int Pixel::App::GetWindowWidth() const
{
	return _windowWidth;
}

int Pixel::App::GetWindowHeight() const
{
	return _windowHeight;
}

bool Pixel::App::CloseRequested() const
{
	return _closeRequested;
}

Pixel::WindowSubsystem Pixel::App::GetWindowSubsystem() const
{
	return _subsystem;
}

bool Pixel::App::IsSDL() const
{
	return (GetWindowSubsystem() == Pixel::WindowSubsystem::SDL);
}

bool Pixel::App::IsWxWidgets() const
{
	return (GetWindowSubsystem() == Pixel::WindowSubsystem::WxWidgets);
}

HWND Pixel::App::GetWindowHandle() const
{
	if (IsSDL())
	{
		return _SDLSysInfo.info.win.window;
	}
	else if (IsWxWidgets())
	{
		return (HWND)_wxWindow->GetHandle();
	}
}
