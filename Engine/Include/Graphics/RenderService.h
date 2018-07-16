#pragma once

#include "Include/Common.h"

#include "Include/Type/Size.h"

#include <SDL/SDL.h>

namespace Pixel {

	/**
	*  TODO
	*/
	class PIXEL_API RenderService
	{
		public:

			/**
			*  Class constructor
			*  This function can throw a Pixel::Exception::FatalError
			*/
			RenderService();

			/**
			*  Class deconstructor
			*/
			virtual ~RenderService();

			/**
			*  Class singleton getter
			*  This function can throw a Pixel::Exception::FatalError
			*/
			static Pixel::RenderService* Singleton();

			void Initialize();

			void SetupFrame();

			void Clear();

			void RenderWorldObjects(void);

			void RenderSystemObjects();

			void RenderScreenGuis(void);

			void RenderSystemGuis();

			/**
			*  Sets whether or not the render system will render vertices in wireframe
			*  This does not effect GUI elements or system objects
			*/
			void SetWireframeEnabled(bool);

			/**
			*  Sets the rendering viewport for OpenGL
			*  Values should be something like (800, 600), (1920, 1080), etc
			*/
			void SetViewport(int width, int height);

			/**
			*  Sets the rendering aspect ratio for OpenGL
			*  Values should be something like (4, 3), (16, 9), etc
			*/
			void SetAspectRatio(int width, int height);

			/**
			*  TODO
			*/
			void SetGLContext(SDL_GLContext);

		private:

			/**
			*  The singleton instance for this class (only one Pixel::RenderService can exist)
			*  See Pixel::RenderService::Singleton()
			*/
			static Pixel::RenderService* instance;

			SDL_GLContext _glContext;
			Pixel::Type::Size _viewportSize;
			Pixel::Type::Size _aspectRatio;
			bool _wireframeEnabled = false;
	};

}