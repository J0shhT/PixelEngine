/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Graphics/RenderService.cpp
*/

#include "Include/Graphics/RenderService.h"

#include "Include/PixelError.h"
#include "Include/PixelOutput.h"
#include "Include/Core/PixelApp.h"
#include "Include/Core/SceneManager.h"
#include "Include/Core/SoundService.h"

#include "Include/Object/RenderableObject.h"
#include "Include/Object/BasicTextGui.h"

#include "Include/Graphics/GuiService.h"

#include "Include/Physics/PhysicsService.h"

#include <GL/glew.h>
#include <GL/glut.h>

PIXEL_DECLARE_SINGLETON(Pixel::RenderService);

Pixel::RenderService::RenderService()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::RenderService);

	_backgroundColor = Pixel::Type::Color(0.25f);

	//Create camera
	_currentCamera = Pixel::SceneManager::Singleton()->CreateObject<Pixel::Object::Camera>();
	_currentCamera->SetName("Camera");
}

Pixel::RenderService::~RenderService()
{
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::RenderService);
}

void Pixel::RenderService::Initialize()
{
	if (IsInitialized())
	{
		PixelWarning("RenderService::Initialize() - RenderService is already initialized");
		return;
	}

	glewExperimental = GL_TRUE;

	if (glewInit() == GLEW_OK)
	{
		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info, "RenderService::Initialize() - GLEW initialized");
	}
	else
	{
		PixelFatalError("GLEW initialization failed (error " + std::to_string(glewInit()) + std::string(")"));
	}

	/* Load engine vertex shader */
	auto vertexShader = Pixel::Graphics::CreateShader(Pixel::Graphics::ShaderType::VertexShader);
#ifdef _DEBUG
	vertexShader->Load(DEBUG_BUILD_FILE_DIR "Shaders/Vertex.glsl");
#else
	vertexShader->Load("Shaders/Vertex.glsl");
#endif
	AddShader(vertexShader);

	/* Load engine fragment shader */
	auto fragmentShader = Pixel::Graphics::CreateShader(Pixel::Graphics::ShaderType::FragmentShader);
#ifdef _DEBUG
	fragmentShader->Load(DEBUG_BUILD_FILE_DIR "Shaders/Fragment.glsl");
#else
	fragmentShader->Load("Shaders/Fragment.glsl");
#endif
	AddShader(fragmentShader);

	//Link shaders
	LinkShaders();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glCreateVertexArrays(1, &_glVertexArrays);
	glBindVertexArray(_glVertexArrays);
	glUseProgram(_glProgram);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	_isInitialized = true;
}

void Pixel::RenderService::SetupFrame()
{
	if (_wireframeEnabled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glViewport(0, 0, (GLsizei)_viewportSize.GetWidth(), (GLsizei)_viewportSize.GetHeight());
}

void Pixel::RenderService::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(_backgroundColor.GetRed(), _backgroundColor.GetGreen(), _backgroundColor.GetBlue(), 1.0f);
}

void Pixel::RenderService::RenderWorldObjects()
{
	glUseProgram(_glProgram);
	auto gameObjects = Pixel::SceneManager::Singleton()->GetObjects();
	for (auto iter = gameObjects.cbegin(); iter != gameObjects.cend(); ++iter)
	{
		std::shared_ptr<Pixel::Object::Object> object = iter->second;
		if (object->IsA<Pixel::Object::RenderableObject>())
		{
			std::shared_ptr<Pixel::Object::RenderableObject> renderableObject = std::dynamic_pointer_cast<Pixel::Object::RenderableObject>(object);
			object.reset();
			renderableObject->Render();
			renderableObject.reset();
		}
	}
	glUseProgram(0);
}

void Pixel::RenderService::RenderSystemObjects()
{

}

void Pixel::RenderService::RenderScreenGuis()
{
	glUseProgram(_glProgram);
	auto guiObjects = Pixel::GuiService::Singleton()->GetGuiObjects();
	for (auto iter = guiObjects.cbegin(); iter != guiObjects.cend(); ++iter)
	{
		std::shared_ptr<Pixel::Object::GuiObject> object = iter->second;
		if (object->IsVisible())
		{
			if (object->IsA<Pixel::Object::BasicTextGui>())
			{
				//BasicTextGui object's don't use shaders
				glUseProgram(0);
				object->Render();
				glUseProgram(_glProgram);
			}
			else
			{
				object->Render();
			}
		}
		object.reset();
	}
	glUseProgram(0);
}

void Pixel::RenderService::RenderSystemGuis()
{

}

void Pixel::RenderService::RenderDebugGui()
{
	glUseProgram(0);
	double lastPhysicsFrameDelta = Pixel::PhysicsService::Singleton()->GetLastPhysicsFrameDelta();
	
	/* Render debug GUI backdrop */
	// Yeah, I know fixed function pipeline is bad.
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glBegin(GL_TRIANGLES);
		glVertex2f(0.01f, 0.01f);
		glVertex2f(0.01f, 0.99f);
		glVertex2f(0.27f, 0.99f);
		glVertex2f(0.27f, 0.99f);
		glVertex2f(0.27f, 0.01f);
		glVertex2f(0.01f, 0.01f);
	glEnd();

	/* Render debug GUI text */
	std::vector<std::string> items = {
		"Pixel Engine " PIXEL_ENGINE_VERSION "",
		"",
		/*
		"---- Render ----",
		"Timing: " + std::string("(todo)"),
		"FPS: " + std::string("(todo)"),
		*/
		"---- Physics ----",
		//"Timing: " + std::string("(todo)"),
		"Frame delta: " + std::to_string(lastPhysicsFrameDelta) + std::string("s"),
		"---- Sound ----",
		//"Timing: " + std::string("(todo)"),
		"Playing: " + std::to_string(Pixel::SoundService::Singleton()->GetTotalPlayingSounds()),
		/*
		"---- Events ----",
		"Timing: " + std::string("(todo)"),
		"Binded: " + std::string("(todo)"),
		*/
		"---- Game ----",
		"Game Objects: " + std::to_string(Pixel::SceneManager::Singleton()->GetObjectCount()),
		"GUI Objects: " + std::to_string(Pixel::GuiService::Singleton()->GetGuiObjectCount()),
		"---- Content ----",
		"Misc: " + std::to_string(Pixel::ContentProvider::Singleton()->GetStats()[Pixel::ContentType::Text]),
		"Textures: " + std::to_string(Pixel::ContentProvider::Singleton()->GetStats()[Pixel::ContentType::Texture]),
		"Sounds: " + std::to_string(Pixel::ContentProvider::Singleton()->GetStats()[Pixel::ContentType::Sound]),
		/*
		"---- Network ----",
		"HTTP GET: " + std::string("(todo)"),
		"HTTP POST: " + std::string("(todo)"),
		*/
	};
	size_t index = 1;
	glColor3f(0.0f, 0.0f, 0.0f);
	for (auto iter = items.cbegin(); iter != items.cend(); iter++)
	{
		glRasterPos2f(0.02f, 0.045f*index);
		for (auto stringIter = (*iter).begin(); stringIter != (*iter).end(); stringIter++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *stringIter);
		}
		index++;
	}
}

void Pixel::RenderService::AddShader(std::shared_ptr<Pixel::Graphics::Shader> shader)
{
	if (_isShadersLinked)
	{
		PixelError("RenderService::AddShader() - Cannot add shader because shaders are already linked");
		return;
	}

	if (!shader->IsLoaded())
	{
		PixelError("RenderService::AddShader() - Cannot add shader because shader is not loaded \"" + shader->GetFilePath() + "\"");
		return;
	}

	_shaders[shader->GetShaderId()] = shader;
}

void Pixel::RenderService::LinkShaders()
{
	if (_isShadersLinked)
	{
		PixelError("RenderService::LinkShaders() - Cannot link shaders because the shaders are already linked");
		return;
	}

	_glProgram = glCreateProgram();

	for (auto iter = _shaders.begin(); iter != _shaders.end(); iter++)
	{
		std::shared_ptr<Pixel::Graphics::Shader> shader = iter->second;

		//Attach shader
		glAttachShader(_glProgram, shader->GetShaderId());
	}

	//Link shaders
	glLinkProgram(_glProgram);

	//Check errors
	GLint linkStatus;
	glGetProgramiv(_glProgram, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_TRUE)
	{
		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info, "RenderService::LinkShaders() - Linked shaders successfully");
	}
	else
	{
		GLint maxLength;
		glGetProgramiv(_glProgram, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_glProgram, maxLength, &maxLength, &errorLog[0]);
		std::stringstream errorLogStream;
		for (auto iter = errorLog.begin(); iter != errorLog.end(); iter++)
		{
			errorLogStream << *iter;
		}
		glDeleteProgram(_glProgram);
		PixelFatalError("RenderService::LinkShaders() - Failed to link shaders: " + errorLogStream.str());
	}

	_shaders.clear();
}

void Pixel::RenderService::SetCurrentCamera(std::shared_ptr<Pixel::Object::Camera> camera)
{
	_currentCamera = camera;
}

std::shared_ptr<Pixel::Object::Camera> Pixel::RenderService::GetCurrentCamera() const
{
	return _currentCamera;
}

void Pixel::RenderService::SetBackgroundColor(Pixel::Type::Color color)
{
	_backgroundColor = color;
}

Pixel::Type::Color Pixel::RenderService::GetBackgroundColor() const
{
	return _backgroundColor;
}

void Pixel::RenderService::SetWireframeEnabled(bool enabled)
{
	_wireframeEnabled = enabled;
}

bool Pixel::RenderService::IsWireframeEnabled() const
{
	return _wireframeEnabled;
}

void Pixel::RenderService::SetViewport(int width, int height)
{
	_viewportSize = Pixel::Type::Size(width, height);
}

void Pixel::RenderService::SetAspectRatio(int width, int height)
{
	_aspectRatio = Pixel::Type::Size(width, height);
}

void Pixel::RenderService::SetGLContext(SDL_GLContext context)
{
	_glContext = context;
}

bool Pixel::RenderService::IsInitialized() const
{
	return _isInitialized;
}

GLuint Pixel::RenderService::GetProgram() const
{
	return _glProgram;
}

glm::mat4 Pixel::RenderService::GetProjectionMatrix() const
{
	return glm::ortho(0.0f, (float)_viewportSize.GetWidth(), (float)_viewportSize.GetHeight(), 0.0f);
}

glm::mat4 Pixel::RenderService::GetCameraMatrix() const
{
	return glm::translate(glm::mat4(), glm::vec3(
		-(float)GetCurrentCamera()->GetPosition().GetX() + (float)_viewportSize.GetWidth() / 2,
		-(float)GetCurrentCamera()->GetPosition().GetY() + (float)_viewportSize.GetHeight() / 2,
		0.0f
	));
}

