#pragma once

#include "Include/Common.h"

#include "Include/Type/Size.h"

#include "Include/Graphics/Shader.h"

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

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
			*  TODO
			*/
			void AddShader(std::shared_ptr<Pixel::Graphics::Shader>);

			/**
			*  TODO
			*/
			void LinkShaders();

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

			/**
			*  TODO
			*/
			bool IsInitialized() const;

			/**
			*  TODO
			*/
			GLuint GetProgram() const;

			/**
			*  TODO
			*/
			glm::mat4 GetProjectionMatrix() const;

		private:

			///todo: document these

			std::map<GLuint, std::shared_ptr<Pixel::Graphics::Shader>> _shaders;
			bool _isShadersLinked;

			GLuint _glProgram;
			GLuint _glVertexArrays;
			SDL_GLContext _glContext;

			glm::mat4 _projectionMatrix;

			Pixel::Type::Size _viewportSize;
			Pixel::Type::Size _aspectRatio;
			bool _wireframeEnabled = false;
			bool _isInitialized = false;
	};

}