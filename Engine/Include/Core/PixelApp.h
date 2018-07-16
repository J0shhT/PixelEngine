#pragma once

#include "Include/Common.h"

#include "Include/Type/Position.h"

#include <SDL/SDL.h>
#undef main

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  TODO
	*/
	class PIXEL_API App 
	{
		public:

			/**
			*  Class constructor
			*  This function can throw a Pixel::Exception::FatalError
			*/
			App();

			/**
			*  Class deconstructor
			*/
			virtual ~App();

			/**
			*  Class singleton getter
			*  This function can throw a Pixel::Exception::FatalError
			*/
			static Pixel::App* Singleton();

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
			*  Set this to true if you do not want Pixel Engine
			to do the window handling for the application.
			*  This will require you to do all window creating
			and management yourself.
			*  When set to true, certain windowing related functions
			for Pixel Engine will throw Pixel::Exception::RuntimeError
			*  This function can allow you to use a different windowing
			library like wxWidgets with Pixel Engine if you know what
			you are doing of course.
			*/
			void UseExternalWindowSystem(bool);

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
			*  Returns whether or not the user has requested for
			the application to close.
			*/
			bool CloseRequested() const;

			/**
			*  TODO
			*/
			double GetLastPhysicsFrameDelta() const;

		private:

			/**
			*  The singleton instance for this class (only one Pixel:App can exist)
			*  See Pixel::App::Singleton()
			*/
			static Pixel::App* instance;

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


			///todo: document these

			bool _closeRequested = false;
			bool _autoGameLoop = false;
			double _lastPhysicsFrameDelta = 0.0;
			bool _debugGuiEnabled = false;
			bool _isUsingExternalWindowSystem = false;

	};

}

#pragma warning(pop)