#pragma once

#include "Include/Common.h"

#include "Include/Type/Size.h"

#include <SDL/SDL.h>

namespace Pixel {

	/**
	*  TODO
	*/
	class PIXEL_API RenderService final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::RenderService);

		public:

			/**
			*  Class constructor
			*/
			RenderService();

			/**
			*  Class deconstructor
			*/
			~RenderService();

			/**
			*  TODO
			*/
			void Initialize();

			/**
			*  TODO
			*/
			void SetupFrame();

			/**
			*  TODO
			*/
			void Clear();

			/**
			*  TODO
			*/
			void RenderWorldObjects(void);

			/**
			*  TODO
			*/
			void RenderSystemObjects();

			/**
			*  TODO
			*/
			void RenderScreenGuis(void);

			/**
			*  TODO
			*/
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

			///todo: document these

			SDL_GLContext _glContext;
			Pixel::Type::Size _viewportSize;
			Pixel::Type::Size _aspectRatio;
			bool _wireframeEnabled = false;
	};

}