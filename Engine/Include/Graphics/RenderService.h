/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Graphics/RenderService.h
*/

#pragma once

#include "Include/Common.h"

#include "Include/Object/Camera.h"
#include "Include/Type/Size.h"
#include "Include/Graphics/Shader.h"

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  The Pixel::RenderService is a singleton service which handles
	all high-level rendering calls in Pixel Engine. This service is responsible
	for going through all renderable objects and calling their render functions.

	*  This service is also responsible for shaders.

	*  This service also contains functions to toggle certain rendering
	and graphics relating properties/options/settings.
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
			*  Initializes all systems required for RenderService to function.
			*  This function must be called before you use anything in this service!
			*  Currently, this function does the following things:
			- Intialize GLEW
			- Load, compile, and link vertex and fragment shader
			- Set various OpenGL settings
			- Create OpenGL vertex arrays
			*/
			void Initialize();

			/**
			*  Prepares the engine to render a frame.
			*  This function must be called each time before a frame is rendered.
			*/
			void SetupFrame();

			/**
			*  Clears the frame (color and depth buffer)
			*  This function should be called before a new frame is rendered,
			and after RenderService::SetupFrame() is called.
			*/
			void Clear();

			/**
			*  Renders all world objects in the game.
			*/
			void RenderWorldObjects();

			/**
			*  Renders all world objects in the game that were created by the engine.
			*/
			void RenderSystemObjects();

			/**
			*  Renders all gui objects in the game.
			*/
			void RenderScreenGuis();

			/**
			*  Renders all gui objects in the game that were created by the engine.
			*/
			void RenderSystemGuis();

			/**
			*  Renders the Pixel Engine debug information gui.
			*/
			void RenderDebugGui();

			/**
			*  Adds an already compiled Pixel::Graphics::Shader to be linked into the engine.
			*/
			void AddShader(std::shared_ptr<Pixel::Graphics::Shader>);

			/**
			*  Links all currently added shaders into the engine.
			*  This can only be called once.
			*/
			void LinkShaders();

			/**
			*  Sets the current camera object to render the view from.
			*  A camera object is created automatically (and set as current)
			when the RenderService is created.
			*/
			void SetCurrentCamera(std::shared_ptr<Pixel::Object::Camera>);

			/**
			*  Gets the current camera object that the view is being rendered from.
			*/
			std::shared_ptr<Pixel::Object::Camera> GetCurrentCamera() const;

			/**
			*  Sets the background color to be rendered.
			*  This is the color that is rendered when a frame is cleared.
			*/
			void SetBackgroundColor(Pixel::Type::Color);

			/**
			*  Returns the currently set background color.
			*  See RenderService::SetBackgroundColor()
			*/
			Pixel::Type::Color GetBackgroundColor() const;

			/**
			*  Sets whether or not the render system will render vertices in wireframe.
			*  This does not effect gui objects or system game objects.
			*/
			void SetWireframeEnabled(bool);

			/**
			*  Returns whether or not wireframe mode is currently enabled.
			*/
			bool IsWireframeEnabled() const;

			/**
			*  Sets the rendering viewport for OpenGL.
			*  Values should be something like (800, 600), (1920, 1080), etc.
			*/
			void SetViewport(int width, int height);

			/**
			*  Sets the rendering aspect ratio for OpenGL.
			*  Values should be something like (4, 3), (16, 9), etc.
			*/
			void SetAspectRatio(int width, int height);

			/**
			*  Sets the current SDL OpenGL context.
			*  This function is used internally and you shouldn't really use it.
			*/
			void SetGLContext(SDL_GLContext);

			/**
			*  Returns whether or not the RenderService has been initialized.
			*/
			bool IsInitialized() const;

			/**
			*  Returns the OpenGL ID of the shader program.
			*/
			GLuint GetProgram() const;

			/**
			*  Returns a glm::mat4 of the current projection matrix.
			*/
			glm::mat4 GetProjectionMatrix() const;

			/**
			*  Returns a glm::mat4 of the current camera matrix.
			*/
			glm::mat4 GetCameraMatrix() const;

		private:

			std::map<GLuint, std::shared_ptr<Pixel::Graphics::Shader>> _shaders;
			bool _isShadersLinked;
			std::shared_ptr<Pixel::Object::Camera> _currentCamera;
			Pixel::Type::Color _backgroundColor;
			Pixel::Type::Size _viewportSize;
			Pixel::Type::Size _aspectRatio;
			bool _wireframeEnabled = false;
			bool _isInitialized = false;

			GLuint _glProgram;
			GLuint _glVertexArrays;
			SDL_GLContext _glContext;
	};

}

#pragma warning(pop)