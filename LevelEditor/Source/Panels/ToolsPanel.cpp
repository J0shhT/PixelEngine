#include "Include/Panels/ToolsPanel.h"

#include <wx/app.h>
#include <wx/tglbtn.h>

#include "Include/Windows/PixelEditor.h"
#include "Include/Enums.h"

wxBEGIN_EVENT_TABLE(Pixel::Editor::ToolsPanel, wxRibbonPage)
wxEND_EVENT_TABLE();

//#define PIXEL_TOOLS_BUTTON_SIZE 30
//#define PIXEL_TOOLS_BUTTON_PADDING 10

std::vector<Pixel::Editor::ToolButton> ToolButtons_ObjectTools;

Pixel::Editor::ToolsPanel::ToolsPanel(wxRibbonBar* parent) : wxRibbonPage(parent, ID_ToolsPanel_RibbonPage, "Tools", wxNullBitmap)
{
	/* Create panel */
	wxRibbonPanel* objectToolsPanel = new wxRibbonPanel(this, ID_ToolsPanel_ObjectToolsPanel, "Object", wxNullBitmap, wxDefaultPosition, wxDefaultSize,
		wxRIBBON_PANEL_NO_AUTO_MINIMISE);

	/* Create object tools */
	wxRibbonToolBar* objectToolsToolbar = new wxRibbonToolBar(objectToolsPanel, ID_ToolsPanel_ObjectToolbar);
	_objectToolbar = objectToolsToolbar;

	//Select Tool
	Pixel::Editor::ToolButton selectToolButton = {
		"Select Tool",
		"Use this tool to select objects in the game world.",
		ID_ToolsPanel_SelectTool,
		wxBITMAP_PNG(UI_ICON_TOOL_SELECT)
	};
	selectToolButton.eventHandler = &Pixel::Editor::ToolsPanel::OnSelectTool;
	ToolButtons_ObjectTools.push_back(selectToolButton);

	//Move Tool
	Pixel::Editor::ToolButton moveToolButton = {
		"Move Tool",
		"Use this tool to move objects around in the game world.",
		ID_ToolsPanel_MoveTool,
		wxBITMAP_PNG(UI_ICON_TOOL_MOVE)
	};
	moveToolButton.eventHandler = &Pixel::Editor::ToolsPanel::OnMoveTool;
	ToolButtons_ObjectTools.push_back(moveToolButton);

	//Size Tool
	Pixel::Editor::ToolButton sizeToolButton = {
		"Size Tool",
		"Use this tool to change the size of objects in the game world.",
		ID_ToolsPanel_SizeTool,
		wxBITMAP_PNG(UI_ICON_TOOL_SIZE)
	};
	sizeToolButton.eventHandler = &Pixel::Editor::ToolsPanel::OnSizeTool;
	ToolButtons_ObjectTools.push_back(sizeToolButton);

	/* Generate object tool buttons */
	int currentOrder = 1;
	for (auto iter = ToolButtons_ObjectTools.begin(); iter != ToolButtons_ObjectTools.end(); iter++)
	{
		auto toolButtonStruct = *iter;
		objectToolsToolbar->AddToggleTool(toolButtonStruct.toolId, toolButtonStruct.icon, toolButtonStruct.toolName + std::string(" - ") + toolButtonStruct.toolDesc);
		objectToolsToolbar->Bind(wxEVT_RIBBONTOOLBAR_CLICKED, toolButtonStruct.eventHandler, this, toolButtonStruct.toolId);
		currentOrder++;
	}
}

void Pixel::Editor::ToolsPanel::OnSelectTool(wxRibbonToolBarEvent& event)
{
	if (event.IsChecked())
	{
		/* Mark other tool UI buttons as not enabled (only 1 object tool can be enabled at once!) */
		_objectToolbar->ToggleTool(ID_ToolsPanel_MoveTool, false);
		_objectToolbar->ToggleTool(ID_ToolsPanel_SizeTool, false);

		//Enable Select Tool in engine
		Pixel::SelectionService::Singleton()->EnableSelectTool(true);
	}
	else
	{
		//Disable Select Tool in engine
		Pixel::SelectionService::Singleton()->EnableSelectTool(false);
	}
}

void Pixel::Editor::ToolsPanel::OnMoveTool(wxRibbonToolBarEvent & event)
{
	if (event.IsChecked())
	{
		/* Mark other tool UI buttons as not enabled (only 1 object tool can be enabled at once!) */
		_objectToolbar->ToggleTool(ID_ToolsPanel_SelectTool, false);
		_objectToolbar->ToggleTool(ID_ToolsPanel_SizeTool, false);

		//Enable Move Tool in engine
		Pixel::SelectionService::Singleton()->EnableMoveTool(true);
	}
	else
	{
		//Disable Move Tool in engine
		Pixel::SelectionService::Singleton()->EnableMoveTool(false);
	}
}

void Pixel::Editor::ToolsPanel::OnSizeTool(wxRibbonToolBarEvent & event)
{
	if (event.IsChecked())
	{
		/* Mark other tool UI buttons as not enabled (only 1 object tool can be enabled at once!) */
		_objectToolbar->ToggleTool(ID_ToolsPanel_MoveTool, false);
		_objectToolbar->ToggleTool(ID_ToolsPanel_SelectTool, false);

		//Enable Size Tool in engine
		Pixel::SelectionService::Singleton()->EnableSizeTool(true);
	}
	else
	{
		//Disable Size Tool in engine
		Pixel::SelectionService::Singleton()->EnableSizeTool(false);
	}
}
