#include "Include/Graphics/Shader.h"

#include "Include/PixelError.h"
#include "Include/PixelOutput.h"

Pixel::Graphics::Shader::Shader()
{
}

Pixel::Graphics::Shader::~Shader()
{
}

bool Pixel::Graphics::Shader::IsLoaded() const
{
	return _isLoaded;
}

GLuint Pixel::Graphics::Shader::GetShaderId() const
{
	return _shaderId;
}

std::string Pixel::Graphics::Shader::GetFilePath() const
{
	return _filePath;
}

Pixel::Graphics::ShaderType Pixel::Graphics::Shader::GetShaderType() const
{
	return _shaderType;
}



Pixel::Graphics::VertexShader::VertexShader()
{
	_shaderType = Pixel::Graphics::ShaderType::VertexShader;
}

Pixel::Graphics::VertexShader::~VertexShader()
{
	glDeleteShader(_shaderId);
	_isLoaded = false;
}

bool Pixel::Graphics::VertexShader::Load(std::string filePath)
{
	//Read file
	_filePath = filePath;
	std::ifstream shaderFile(filePath);
	if (!shaderFile.good()) {
		throw Pixel::Exception::FatalError("VertexShader::Load() - Error reading file \"" + filePath + "\"");
	}
	std::stringstream shaderBuffer;
	shaderBuffer << shaderFile.rdbuf();
	std::string shaderSourceStr = shaderBuffer.str();
	const GLchar* shaderSource = (const GLchar*)shaderSourceStr.c_str();

	//Compile shader
	_shaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_shaderId, 1, &shaderSource, NULL);
	glCompileShader(_shaderId);

	//Check errors
	GLint shaderStatus;
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &shaderStatus);
	if (shaderStatus == GL_TRUE)
	{
		_isLoaded = true;
		Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Info, "VertexShader::Load() - Compiled \"%s\"", filePath.c_str());
		return true;
	}
	else
	{
		GLint maxLength;
		glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(_shaderId, maxLength, &maxLength, &errorLog[0]);
		std::stringstream errorLogStream;
		for (auto iter = errorLog.begin(); iter != errorLog.end(); iter++)
		{
			errorLogStream << *iter;
		}
		glDeleteShader(_shaderId);
		throw Pixel::Exception::FatalError("VertexShader::Load() - Failed to compile shader: " + errorLogStream.str());
	}
	return false;
}



Pixel::Graphics::FragmentShader::FragmentShader()
{
	_shaderType = Pixel::Graphics::ShaderType::VertexShader;
}

Pixel::Graphics::FragmentShader::~FragmentShader()
{
	glDeleteShader(_shaderId);
	_isLoaded = false;
}

bool Pixel::Graphics::FragmentShader::Load(std::string filePath)
{
	//Read file
	_filePath = filePath;
	std::ifstream shaderFile(filePath);
	if (!shaderFile.good()) {
		throw Pixel::Exception::FatalError("FragmentShader::Load() - Error reading file \"" + filePath + "\"");
	}
	std::stringstream shaderBuffer;
	shaderBuffer << shaderFile.rdbuf();
	std::string shaderSourceStr = shaderBuffer.str();
	const GLchar* shaderSource = (const GLchar*)shaderSourceStr.c_str();

	//Compile shader
	_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_shaderId, 1, &shaderSource, NULL);
	glCompileShader(_shaderId);

	//Check errors
	GLint shaderStatus;
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &shaderStatus);
	if (shaderStatus == GL_TRUE)
	{
		_isLoaded = true;
		Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Info, "FragmentShader::Load() - Compiled \"%s\"", filePath.c_str());
		return true;
	}
	else
	{
		GLint maxLength;
		glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(_shaderId, maxLength, &maxLength, &errorLog[0]);
		std::stringstream errorLogStream;
		for (auto iter = errorLog.begin(); iter != errorLog.end(); iter++)
		{
			errorLogStream << *iter;
		}
		glDeleteShader(_shaderId);
		throw Pixel::Exception::FatalError("FragmentShader::Load() - Failed to compile shader: " + errorLogStream.str());
	}
	return false;
}



std::shared_ptr<Pixel::Graphics::Shader> Pixel::Graphics::CreateShader(Pixel::Graphics::ShaderType type)
{
	switch (type)
	{
		case Pixel::Graphics::ShaderType::VertexShader:
			return std::make_shared<Pixel::Graphics::VertexShader>();

		case Pixel::Graphics::ShaderType::FragmentShader:
			return std::make_shared<Pixel::Graphics::FragmentShader>();

		default:
			return nullptr;
	}
}
