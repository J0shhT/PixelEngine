#pragma once

#include <wx/wx.h>
#include <wx/glcanvas.h>

namespace Pixel::Editor
{
	class GraphicsCanvas : public wxGLCanvas
	{
		public:
			GraphicsCanvas(wxPanel* parent);
			void Idle(wxIdleEvent& event);
			void Paint();

			wxDECLARE_EVENT_TABLE();
	};
}