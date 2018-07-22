#pragma once

#include "Include/Common.h"

#include <GL/glew.h>
#include <GL/glut.h>

namespace Pixel::Graphics {

	enum class ShaderType
	{
		VertexShader,
		FragmentShader,
		ControlShader,
		EvaluationShader,
		GeometryShader
	};

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
			*  TODO
			*/
			bool IsLoaded() const;

			/**
			*  TODO
			*/
			GLuint GetShaderId() const;

			/**
			*  TODO
			*/
			std::string GetFilePath() const;

			/**
			*  TODO
			*/
			Pixel::Graphics::ShaderType GetShaderType() const;

			/**
			*  Abstract function to load+compile shader
			*/
			virtual bool Load(std::string filePath) = 0;

		protected:

			bool _isLoaded;
			GLuint _shaderId;
			std::string _filePath;
			Pixel::Graphics::ShaderType _shaderType;

	};

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
			*  TODO
			*/
			bool Load(std::string filePath);

		protected:


	};

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
			*  TODO
			*/
			bool Load(std::string filePath);

		protected:


	};

	/**
	*  Creates and returns a std::shared_ptr of the specified ShaderType
	*/
	PIXEL_API std::shared_ptr<Pixel::Graphics::Shader> __cdecl CreateShader(Pixel::Graphics::ShaderType);

}