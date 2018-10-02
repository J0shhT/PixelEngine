/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Graphics/Shader.h
*/

#pragma once

#include "Include/Common.h"

#include <GL/glew.h>
#include <GL/glut.h>

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel::Graphics {

	/**
	*  The Pixel::Graphics::ShaderType enum contains all
	currently supported OpenGL shader types that can be used.
	*/
	enum class ShaderType
	{
		VertexShader,
		FragmentShader,
		//ControlShader,
		//EvaluationShader,
		//GeometryShader
	};

	/**
	*  The Pixel::Graphics::Shader class is an abstract class
	used to represent a loaded and compiled shader in the engine.
	*  See below in this file for the specific shader classes.
	*/
	class PIXEL_API Shader
	{
		public:

			/**
			*  Class constructor
			*/
			Shader();

			/**
			*  Class deconstructor
			*/
			virtual ~Shader();

			/**
			*  Returns whether or not the shader is loaded and compiled.
			*/
			bool IsLoaded() const;

			/**
			*  Returns the OpenGL ID of this shader.
			*/
			GLuint GetShaderId() const;

			/**
			*  Returns the file path this shader was loaded from.
			*/
			std::string GetFilePath() const;

			/**
			*  Returns the Pixel::Graphics::ShaderType for this shader.
			*/
			Pixel::Graphics::ShaderType GetShaderType() const;

			/**
			*  Abstract function to load and compile the shader.
			*/
			virtual bool Load(std::string filePath) = 0;

		protected:

			bool _isLoaded;
			GLuint _shaderId;
			std::string _filePath;
			Pixel::Graphics::ShaderType _shaderType;

	};

	/**
	*  The Pixel::Graphics::VertexShader class is used to create
	and load OpenGL Vertex shaders into the engine.
	*/
	class PIXEL_API VertexShader : public Shader
	{
		public:

			/**
			*  Class constructor
			*/
			VertexShader();

			/**
			*  Class deconstructor
			*/
			virtual ~VertexShader();

			/**
			*  Loads and compiles the vertex shader from the specified file path.
			*/
			bool Load(std::string filePath);
	};

	/**
	*  The Pixel::Graphics::Fragment class is used to create
	and load OpenGL Fragment shaders into the engine.
	*/
	class PIXEL_API FragmentShader : public Shader
	{
		public:

			/**
			*  Class constructor
			*/
			FragmentShader();

			/**
			*  Class deconstructor
			*/
			virtual ~FragmentShader();

			/**
			*  Loads and compiles the fragment shader from the specified file path.
			*/
			bool Load(std::string filePath);
	};

	/**
	*  Create and return a std::shared_ptr of the specified 
	Pixel::Graphics::ShaderType as a Pixel::Graphics::Shader.
	*/
	PIXEL_API std::shared_ptr<Pixel::Graphics::Shader> CreateShader(Pixel::Graphics::ShaderType);

}

#pragma warning(pop)