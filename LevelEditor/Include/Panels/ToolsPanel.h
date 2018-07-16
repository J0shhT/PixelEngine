#pragma once

#include <wx/wx.h>
#include <wx/ribbon/panel.h>
#include <wx/ribbon/toolbar.h>
#include <wx/ribbon/bar.h>

namespace Pixel::Editor
{
	class ToolsPanel : public wxRibbonPage
	{
		public:
			ToolsPanel(wxRibbonBar* parent);

		private:
			wxRibbonToolBar* _objectToolbar;

			void OnSelectTool(wxRibbonToolBarEvent& event);
			void OnMoveTool(wxRibbonToolBarEvent& event);
			void OnSizeTool(wxRibbonToolBarEvent& event);

			wxDECLARE_EVENT_TABLE();
	};

	struct ToolButton
	{
		std::string toolName;
		std::string toolDesc;
		int toolId;
		wxBitmap icon;
		void(ToolsPanel::*eventHandler)(wxRibbonToolBarEvent&);
	};

}