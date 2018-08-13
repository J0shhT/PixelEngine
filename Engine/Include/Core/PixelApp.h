#pragma once

#include "Include/Common.h"

#include "Include/Type/Position.h"

#include <SDL/SDL.h>
#include <SDL/SDL_syswm.h>
#undef main

#undef CreateWindow

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  TODO
	*/
	enum class WindowSubsystem
	{
		SDL,
		WxWidgets
	};

	/**
	*  TODO
	*/
	class PIXEL_API App 
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
			virtual ~App();

			/**
			*  Creates a window for the Pixel::App
			*  The window is hidden by default when created.
			*  Only one window can be created per Pixel::App
			*  This function can throw a Pixel::Exception::FatalError
			and a Pixel::Exception::RuntimeError upon certain errors
			*/
			void CreateWindow(std::string title, int width, int height);

			/**
			*  Destroys the current window for the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			void DestroyWindow();

			/**
			*  Processes all events for this Pixel::App
			*  This includes window events and game events.
			*  This also processes and calls custom connected 
			event functions that were made by the user.
			*/
			void ProcessEvents();

			/**
			*  Simulates exactly one physics frame
			*/
			void StepPhysics();

			/**
			*  Renders exactly one graphics frame
			*  This function can throw a Pixel::Exception::RuntimeError
			   if there is no current window associated with the app.
			*  This function can be used without a window being created
			if Pixel::App::UseExternalWindowSystem() is set to true.
			*/
			void Render();

			/**
			*  TODO
			*/
			void UpdateSound();

			/**
			*  Goes through only one step of the pre-made Pixel Engine game loop.
			*/
			void StepGame();

			/**
			*  Starts Pixel Engine's pre-made game loop.
			*  This function does not return until the user
			requests to close the application or the game
			loop is manually stopped.
			*/
			void StartGameLoop();

			/**
			*  Stops the pre-made game loop, if it is running.
			*/
			void StopGameLoop();

			/**
			*  Closes and uninitializes all engine systems relating to this Pixel::App
			*/
			void Close();

			/**
			*  Sets the title bar for the current window of the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			void SetWindowTitle(std::string);
			
			/**
			*  Sets the size for the current window of the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			void SetWindowSize(int width, int height);

			/**
			*  Sets the width for the current window of the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			void SetWindowWidth(int);

			/**
			*  Sets the height for the current window of the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			void SetWindowHeight(int);

			/**
			*  Sets the visibility for the current window of the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			void SetWindowVisible(bool);

			/**
			*  Sets whether or not the Pixel Engine Debug GUI will
			will be displayed on the screen.
			*/
			void SetDebugGuiEnabled(bool);

			/**
			*  Gets the X position of the window for the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			int GetWindowPositionX() const;

			/**
			*  Gets the Y position of the window for the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			int GetWindowPositionY() const;

			/**
			*  Gets the position of the window for the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			Pixel::Type::Position GetWindowPosition() const;

			/**
			*  Gets the width of the window for the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
			*/
			int GetWindowWidth() const;

			/**
			*  Gets the height of the window for the Pixel::App
			*  This function can throw a Pixel::Exception::RuntimeError
			if there is no current window associated with the app.
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

			/**
			*  The windowing subsystem to be used by the engine.
			*  The window subsystem is set via a parameter in the constructor
			of Pixel::App, the default is SDL.
			*  See Pixel::WindowSubsystem enum for available subsystems.
			*/
			Pixel::WindowSubsystem _subsystem;

			/**
			*  For internal usage to check whether or not a window has
			been created for this Pixel::App
			*  See Pixel::App::CreateWindow()
			*/
			bool _hasWindow = false;

			/**
			*  The title set for the window related to this Pixel::App
			*  See Pixel::App::SetWindowTitle()
			*/
			std::string _windowTitle;

			/**
			*  The width for the window size related to this Pixel::App
			*  See Pixel::App::SetWindowWidth()
			*/
			int _windowWidth;

			/**
			*  The height for the window size related to this Pixel::App
			*  See Pixel::App::SetWindowHeight()
			*/
			int _windowHeight;

			/**
			*  Whether or not the window for this Pixel::App is visible.
			*  See Pixel::App::SetWindowVisible()
			*/
			bool _isWindowVisible = false;

			/**
			*  A pointer to the SDL_Window object (internal usage only)
			*  See Pixel::App::CreateWindow()
			*/
			SDL_Window* _window = nullptr;


			/**
			*  A SDL_SysWMinfo struct containing SDL info (internal usage only)
			*/
			SDL_SysWMinfo _SDLSysInfo;

			/**
			*  Whether or not the game was requested to be closed
			either via the user or an internal function call
			*/
			bool _closeRequested = false;

			/**
			*  Whether or not the engine is currently running the
			premade game loop (internal usage only)
			*  See Pixel::App::StartGameLoop()
			*/
			bool _autoGameLoop = false;

			/**
			*  Whether or not to display debug information on screen
			*  See Pixel::App::SetDebugGuiEnabled()
			*/
			bool _debugGuiEnabled = false;

	};

}

#pragma warning(pop)