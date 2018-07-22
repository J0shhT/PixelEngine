#include "Include/Core/PixelApp.h"

#include "Include/PixelError.h"
#include "Include/Core/SceneManager.h"
#include "Include/Core/SelectionService.h"
#include "Include/Core/LogService.h"

#include "Include/Graphics/RenderService.h"

#include "Include/Network/HttpService.h"

#undef CreateWindow

PIXEL_DECLARE_SINGLETON(Pixel::App);

Pixel::App::App()
{
	Pixel::LogService::Singleton();

	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::App);

	//Create singleton services
	new Pixel::HttpService();
	new Pixel::SceneManager();
	new Pixel::RenderService();
	new Pixel::SelectionService();
}

Pixel::App::~App()
{
	Close();

	//Free singleton services
	delete Pixel::SelectionService::Singleton();
	delete Pixel::RenderService::Singleton();
	delete Pixel::SceneManager::Singleton();
	delete Pixel::HttpService::Singleton();

	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::App);

	Pixel::LogService::Singleton()->UploadLogs();
}

void Pixel::App::CreateWindow(std::string title, int width, int height)
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot create window because this Pixel::App is using an external windowing system");
	if (_hasWindow || _window != nullptr)
		throw Pixel::Exception::RuntimeError("A window is already created for this Pixel::App");

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
			//todo: print info message
		}
		else
		{
			throw Pixel::Exception::FatalError("SDL video subsystem initialization failed");
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
		//todo: print info message
		_hasWindow = true;
	}
	else
	{
		throw Pixel::Exception::FatalError("SDL window creation failed");
	}

	//Initialize GLContext
	Pixel::RenderService::Singleton()->SetGLContext(SDL_GL_CreateContext(_window));
}

void Pixel::App::DestroyWindow()
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot destroy window because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot destroy window because no window exists for this Pixel::App");

	SDL_DestroyWindow(_window);
	_hasWindow = false;
	_window = nullptr;
}

void Pixel::App::ProcessEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				_closeRequested = true;
				break;
		}
	}
}

void Pixel::App::StepPhysics()
{
	using namespace std::chrono;
	static auto frameLast = high_resolution_clock::now();
	auto frameNow = high_resolution_clock::now();
	double frameDelta = static_cast<double>(duration_cast<microseconds>(frameNow - frameLast).count()) / 1000000.0;
	frameLast = high_resolution_clock::now();
	_lastPhysicsFrameDelta = frameDelta;
	//todo
}

void Pixel::App::Render()
{
	if (_window == nullptr && !_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot render because no window exists for this Pixel::App");

	static Pixel::RenderService* renderService = Pixel::RenderService::Singleton();

	static bool hasInitialized = false;
	if (!hasInitialized) {
		renderService->Initialize();
		hasInitialized = true;
	}

	renderService->SetupFrame();
	renderService->Clear();

	renderService->RenderWorldObjects();
	renderService->RenderSystemObjects();

	renderService->RenderScreenGuis();
	if (_debugGuiEnabled)
	{
		renderService->RenderSystemGuis();
	}

	if (!_isUsingExternalWindowSystem)
		SDL_GL_SwapWindow(_window);
}

void Pixel::App::UpdateSound()
{
	//todo
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
	if (!_isUsingExternalWindowSystem)
	{
		if (_hasWindow)
			DestroyWindow();

		SDL_Quit();
	}
}

void Pixel::App::SetWindowTitle(std::string title)
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot set window title because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot set window title because no window exists for this Pixel::App");

	SDL_SetWindowTitle(_window, title.c_str());
	_windowTitle = title;
}

void Pixel::App::SetWindowSize(int width, int height)
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot set window size because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot set window size because no window exists for this Pixel::App");

	_windowWidth = width;
	_windowHeight = height;
	SDL_SetWindowSize(_window, width, height);
}

void Pixel::App::SetWindowWidth(int value)
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot set window width because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot set window width because no window exists for this Pixel::App");

	SetWindowSize(value, _windowHeight);
}

void Pixel::App::SetWindowHeight(int value)
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot set window height because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot set window height because no window exists for this Pixel::App");

	SetWindowSize(_windowWidth, value);
}

void Pixel::App::SetWindowVisible(bool value)
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot set window visibility because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot set window visibility because no window exists for this Pixel::App");

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

void Pixel::App::UseExternalWindowSystem(bool enabled)
{
	_isUsingExternalWindowSystem = enabled;
}

int Pixel::App::GetWindowPositionX() const
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot get window position (x) because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot get window position (x) because no window exists for this Pixel::App");

	int value;
	SDL_GetWindowPosition(_window, &value, nullptr);
	return value;
}

int Pixel::App::GetWindowPositionY() const
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot get window position (y) because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot get window position (y) because no window exists for this Pixel::App");

	int value;
	SDL_GetWindowPosition(_window, nullptr, &value);
	return value;
}

Pixel::Type::Position Pixel::App::GetWindowPosition() const
{
	if (_isUsingExternalWindowSystem)
		throw Pixel::Exception::RuntimeError("Cannot get window position because this Pixel::App is using an external windowing system");
	if (_window == nullptr)
		throw Pixel::Exception::RuntimeError("Cannot get window position because no window exists for this Pixel::App");

	int posX;
	int posY;
	SDL_GetWindowPosition(_window, &posX, &posY);
	Pixel::Type::Position position(posX, posY);
	return position;
}

bool Pixel::App::CloseRequested() const
{
	return _closeRequested;
}

double Pixel::App::GetLastPhysicsFrameDelta() const
{
	return _lastPhysicsFrameDelta;
}