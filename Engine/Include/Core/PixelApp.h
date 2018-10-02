/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/PixelApp.h
*/

#pragma once

#include "Include/Common.h"

#include "Include/Type/Position.h"

#include <wx/wx.h>
#include <SDL/SDL.h>
#include <SDL/SDL_syswm.h>

#undef main
#undef CreateWindow

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  The Pixel::WindowSubsystem contains the windowing subsystem
	libraries that Pixel Engine supports. 
	*/
	enum class WindowSubsystem
	{
		SDL,
		WxWidgets
	};

	/**
	*  The Pixel::App is the main class for Pixel Engine. Every application
	that uses Pixel Engine must construct a Pixel::App class manually.

	*  The Pixel::App class is responsible for initializing all engine subsystems.

	*  The Pixel::App is where all the high-level magic happens, such as the game-loop.

	*  Pixel Engine is able to deal with either SDL or WxWidgets as a windowing subsystem.
	The default windowing subsystem is SDL, but you can change this in the constructor
	of Pixel::App.

	*  The SDL subsystem is recommended when you are just creating a game with Pixel Engine.
	You can use WxWidgets subsystem if you require window GUI interfaces in your program, like
	if you were creating a level editor.
	*/
	class PIXEL_API App final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::App);

		public:

			/**
			*  Class constructor
			*/
			App(Pixel::WindowSubsystem subsystem = Pixel::WindowSubsystem::SDL);

			/**
			*  Class deconstructor
			*/
			~App();

			/**
			*  Creates a window for the Pixel::App
			*  The window is hidden by default when created.
			*  Only one window can be created per Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			void CreateWindow(std::string title, int width, int height);

			/**
			*  Destroys the current window for the Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			void DestroyWindow();

			/**
			*  Sets the main wxWindow used for this program.
			*  This must be properly set for certain events to work in Pixel Engine.
			*  This function should only be used if you are using the
			wxWidgets windowing subsystem.
			*/
			void SetWxWidgetsWindow(wxWindow*);

			/**
			*  Processes all events for this Pixel::App, this includes window events,
			input events, game events, and custom events.
			*/
			void ProcessEvents();

			/**
			*  Simulates exactly one physics frame.
			*  Physics is simulated in this order:
			- Time and setup frame
			- Simulate world objects
			- Simulate system objects
			- Update current camera
			*/
			void StepPhysics();

			/**
			*  Renders exactly one graphics frame.
			*  Rendering is handled in this order:
			- Setup frame
			- Clear screen
			- Render world objects
			- Render system objects
			- Render screen guis
			- Render system guis
			- Swap frames
			*/
			void Render();

			/**
			*  Updates the sound engine for the game.
			*/
			void UpdateSound();

			/**
			*  Goes through only one step of the pre-made Pixel Engine game loop.
			*/
			void StepGame();

			/**
			*  Starts Pixel Engine's pre-made game loop.
			*  This function does not return until the user requests to close 
			the application or the game loop is manually stopped.
			*/
			void StartGameLoop();

			/**
			*  Stops the pre-made game loop, if it is running.
			*/
			void StopGameLoop();

			/**
			*  Closes and uninitializes all engine systems relating to this Pixel::App.
			*/
			void Close();

			/**
			*  Sets the title bar for the current window of the Pixel::App.
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			void SetWindowTitle(std::string);
			
			/**
			*  Sets the size for the current window of the Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			void SetWindowSize(int width, int height);

			/**
			*  Sets the width for the current window of the Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			void SetWindowWidth(int);

			/**
			*  Sets the height for the current window of the Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			void SetWindowHeight(int);

			/**
			*  Sets the visibility for the current window of the Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			void SetWindowVisible(bool);

			/**
			*  Sets whether or not the Pixel Engine Debug GUI will
			will be displayed on the screen.
			*/
			void SetDebugGuiEnabled(bool);

			/**
			*  Returns whether or not the Pixel Engine Debug GUI is enabled.
			*/
			bool IsDebugGuiEnabled() const;

			/**
			*  Gets the X position of the window for the Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			int GetWindowPositionX() const;

			/**
			*  Gets the Y position of the window for the Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			int GetWindowPositionY() const;

			/**
			*  Gets the position of the window for the Pixel::App
			*  This function should only be used if you are using the
			SDL windowing subsystem.
			*/
			Pixel::Type::Position GetWindowPosition() const;

			/**
			*  Gets the width of the window for the Pixel::App
			*/
			int GetWindowWidth() const;

			/**
			*  Gets the height of the window for the Pixel::App
			*/
			int GetWindowHeight() const;

			/**
			*  Returns whether or not the user has requested for
			the application to close.
			*/
			bool CloseRequested() const;

			/**
			*  Returns the windowing subsystem currently being used.
			*/
			Pixel::WindowSubsystem GetWindowSubsystem() const;

			/**
			*  Returns whether or not the windowing subsystem is set to SDL.
			*/
			bool IsSDL() const;

			/**
			*  Returns whether or not the windowing subsystem is set to WxWidgets.
			*/
			bool IsWxWidgets() const;

			/**
			*  Returns the window handle for the window for the Pixel::App
			*/
			HWND GetWindowHandle() const;

		private:

			Pixel::WindowSubsystem _subsystem;
			bool _hasWindow = false;
			std::string _windowTitle;
			int _windowWidth;
			int _windowHeight;
			bool _isWindowVisible = false;
			bool _closeRequested = false;
			bool _autoGameLoop = false;
			bool _debugGuiEnabled = false;

			wxWindow* _wxWindow = nullptr;
			SDL_Window* _window = nullptr;
			SDL_SysWMinfo _SDLSysInfo;

	};

}

namespace Pixel {

	/**
	*  Validates whether or not the specified engine version
	is compatible with the loaded engine DLL.
	*  This function should always be called at the start of
	your application.
	*  This function throws a Pixel::Exception::FatalError
	if the check fails.
	*/
	PIXEL_API void ValidateEngineVersion(std::string version);

}

#pragma warning(pop)