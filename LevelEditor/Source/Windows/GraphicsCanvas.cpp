#include <PixelEngine.h>

#include "Include/Windows/GraphicsCanvas.h"

#include <wx/app.h>

#include "Include/Windows/PixelEditor.h"
#include "Include/Enums.h"

wxBEGIN_EVENT_TABLE(Pixel::Editor::GraphicsCanvas, wxGLCanvas)
	EVT_IDLE(Pixel::Editor::GraphicsCanvas::Idle)
wxEND_EVENT_TABLE();

Pixel::Editor::GraphicsCanvas::GraphicsCanvas(wxPanel* parent) : wxGLCanvas(parent, ID_GraphicsCanvas, NULL, wxDefaultPosition, wxSize(800, 600))
{
	wxGLContext *glContext = new wxGLContext(this);
	this->SetCurrent(*glContext);
}
void Pixel::Editor::GraphicsCanvas::Idle(wxIdleEvent& event)
{
	static Pixel::UserInputService* userInputService = Pixel::UserInputService::Singleton();
	userInputService->PollWxWidgets();
	Paint();
	event.RequestMore();
}
void Pixel::Editor::GraphicsCanvas::Paint()
{
	static Pixel::App* app = Pixel::App::Singleton();
	static Pixel::RenderService* renderService = Pixel::RenderService::Singleton();
	wxClientDC(this);
	renderService->SetViewport(GetSize().x, GetSize().y);
	app->StepGame();
	this->SwapBuffers();
}