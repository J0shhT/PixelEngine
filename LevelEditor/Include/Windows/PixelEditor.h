#pragma once

#include <wx/wx.h>
#include <PixelEngine.h>

namespace Pixel::Editor
{
	class App : public wxApp
	{
		public:
			virtual bool OnInit();
			virtual int OnExit();
	};

	class CoreWindow : public wxFrame
	{
		public:
			CoreWindow();
		private:
			void OnFileNew(wxCommandEvent& event);
			void OnFileOpen(wxCommandEvent& event);
			void OnFileClose(wxCommandEvent& event);
			void OnFileSave(wxCommandEvent& event);
			void OnFileSaveAs(wxCommandEvent& event);
			void OnFileSettings(wxCommandEvent& event);
			void OnFileExit(wxCommandEvent& event);
			void OnViewDebugInfo(wxCommandEvent& event);
			void OnHelpAbout(wxCommandEvent& event);

			void OnDevTestRandomRect(wxCommandEvent& event);

			wxDECLARE_EVENT_TABLE();
	};

}

wxDECLARE_APP(Pixel::Editor::App);