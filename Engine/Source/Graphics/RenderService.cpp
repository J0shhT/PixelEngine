#include "Include/Graphics/RenderService.h"

#include "Include/PixelError.h"
#include "Include/Core/PixelApp.h"

#include <GL/glew.h>
#include <GL/glut.h>

PIXEL_DECLARE_SINGLETON(Pixel::RenderService);

Pixel::RenderService::RenderService()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::RenderService);
}

Pixel::RenderService::~RenderService()
{
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::RenderService);
}

void Pixel::RenderService::Initialize()
{
	if (glewInit() == GLEW_OK)
	{
		//todo: print info message
	}
	else
	{
		throw Pixel::Exception::FatalError(std::string("GLEW initialization failed (error ") + std::to_string(glewInit()) + std::string(")"));
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
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
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
}

void Pixel::RenderService::RenderWorldObjects(void)
{

}

void Pixel::RenderService::RenderSystemObjects()
{

}

void Pixel::RenderService::RenderScreenGuis(void)
{

}

void Pixel::RenderService::RenderSystemGuis()
{
	double lastPhysicsFrameDelta = Pixel::App::Singleton()->GetLastPhysicsFrameDelta();
	glColor3f(1.0f, 0.0f, 1.0f);
	glRasterPos2f(-0.97, 0.87f);
	std::string frameDeltaSecText = std::to_string(lastPhysicsFrameDelta) + std::string("s");
	for (auto iter = frameDeltaSecText.begin(); iter != frameDeltaSecText.end(); iter++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *iter);
	}
	glRasterPos2f(-0.97, 0.93f);
	std::string fpsCounterText = std::to_string(static_cast<int>(1.0 / lastPhysicsFrameDelta)) + std::string(" FPS");
	for (auto iter = fpsCounterText.begin(); iter != fpsCounterText.end(); iter++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *iter);
	}
}

void Pixel::RenderService::SetWireframeEnabled(bool enabled)
{
	_wireframeEnabled = enabled;
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

