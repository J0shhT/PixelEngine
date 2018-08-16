#include "Include/Windows/PixelEditor.h"

#include <wx/artprov.h>
#include <wx/imagpng.h>

#include "Include/VersionInfo.h"
#include "Include/Enums.h"
#include "Include/Windows/GraphicsCanvas.h"
#include "Include/Panels/ToolsPanel.h"

#include <random>

void MouseClickEvent(const Pixel::InputEvent& e)
{
	PixelPrintf("Mouse clicked! (button %d) (%d, %d)", e.mouseButton, e.mouseX, e.mouseY);
}

#define PIXEL_WINDOW_WIDTH 815
#define PIXEL_WINDOW_HEIGHT 732

wxBEGIN_EVENT_TABLE(Pixel::Editor::CoreWindow, wxFrame)
	//File Menu
	EVT_MENU(ID_CoreWindow_NewLevel, Pixel::Editor::CoreWindow::OnFileNew)
	EVT_MENU(ID_CoreWindow_OpenLevel, Pixel::Editor::CoreWindow::OnFileOpen)
	EVT_MENU(ID_CoreWindow_SaveLevel, Pixel::Editor::CoreWindow::OnFileSave)
	EVT_MENU(ID_CoreWindow_SaveLevelNew, Pixel::Editor::CoreWindow::OnFileSaveAs)
	EVT_MENU(ID_CoreWindow_Settings, Pixel::Editor::CoreWindow::OnFileSettings)
	EVT_MENU(wxID_EXIT, Pixel::Editor::CoreWindow::OnFileExit)
	//Help Menu
	EVT_MENU(wxID_ABOUT, Pixel::Editor::CoreWindow::OnHelpAbout)
	//DevTest Menu
	EVT_MENU(ID_CoreWindow_DevTest_RandomRect, Pixel::Editor::CoreWindow::OnDevTestRandomRect)
wxEND_EVENT_TABLE();

bool Pixel::Editor::App::OnInit()
{
	//Create Pixel::App (required for Pixel Engine)
	try {
		Pixel::App* app = new Pixel::App(Pixel::WindowSubsystem::WxWidgets);
		app->SetDebugGuiEnabled(true);

		//Create PNG handler (for using wxBitmap with PNG files)
		wxImage::AddHandler(new wxPNGHandler);

		//Create main editor window
		Pixel::Editor::CoreWindow *mainWindow = new Pixel::Editor::CoreWindow();
		mainWindow->Show(true);

		app->SetWxWidgetsWindow(mainWindow);

		Pixel::UserInputService::Singleton()->Bind(Pixel::InputEventType::MouseDown, &MouseClickEvent);
	}
	catch (Pixel::Exception::FatalError)
	{
		Pixel::LogService::Singleton()->UploadLogs(Pixel::LogType::CrashLog);
		return false;
	}
	return true;
}

int Pixel::Editor::App::OnExit()
{
	delete Pixel::App::Singleton();
	return 0;
}

Pixel::Editor::CoreWindow::CoreWindow()
	: wxFrame(NULL, ID_CoreWindow, "Pixel Editor", wxDefaultPosition, wxSize(PIXEL_WINDOW_WIDTH, PIXEL_WINDOW_HEIGHT), 
		wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN
	)
{
	SetIcon(wxICON(APP_ICON));

	//File Dropdown Menu  //////////////////////////////////////
	wxMenu *menuFile = new wxMenu;

	//File -> New...
	wxMenuItem *menuFile_NewLevel = new wxMenuItem(menuFile, ID_CoreWindow_NewLevel, "&New...\tCtrl+N");
	menuFile_NewLevel->SetBitmap(wxBITMAP_PNG(UI_ICON_NEW));
	menuFile->Append(menuFile_NewLevel);

	//File -> Open...
	wxMenuItem *menuFile_OpenLevel = new wxMenuItem(menuFile, ID_CoreWindow_OpenLevel, "&Open...\tCtrl+O");
	menuFile_OpenLevel->SetBitmap(wxBITMAP_PNG(UI_ICON_OPEN));
	menuFile->Append(menuFile_OpenLevel);

	//File -> Close
	wxMenuItem *menuFile_CloseLevel = new wxMenuItem(menuFile, ID_CoreWindow_CloseLevel, "&Close");
	menuFile->Append(menuFile_CloseLevel);

	menuFile->AppendSeparator();

	//File -> Save
	wxMenuItem *menuFile_SaveLevel = new wxMenuItem(menuFile, ID_CoreWindow_SaveLevel, "&Save\tCtrl+S");
	menuFile_SaveLevel->SetBitmap(wxBITMAP_PNG(UI_ICON_SAVE));
	menuFile->Append(menuFile_SaveLevel);

	//File -> Save As...
	wxMenuItem *menuFile_SaveLevelNew = new wxMenuItem(menuFile, ID_CoreWindow_SaveLevelNew, "&Save As...");
	menuFile_SaveLevelNew->SetBitmap(wxBITMAP_PNG(UI_ICON_SAVE_AS));
	menuFile->Append(menuFile_SaveLevelNew);

	menuFile->AppendSeparator();

	//File -> Settings...
	wxMenuItem *menuFile_Settings = new wxMenuItem(menuFile, ID_CoreWindow_Settings, "&Settings...");
	menuFile_Settings->SetBitmap(wxBITMAP_PNG(UI_ICON_SETTINGS));
	menuFile->Append(menuFile_Settings);

	menuFile->AppendSeparator();

	//File -> Quit
	wxMenuItem *menuFile_Quit = new wxMenuItem(menuFile, wxID_EXIT, "&Quit\tAlt+F4", "Quit the application");
	menuFile_Quit->SetBitmap(wxBITMAP_PNG(UI_ICON_EXIT));
	menuFile->Append(menuFile_Quit);

	menuFile->Enable(ID_CoreWindow_CloseLevel, false);
	menuFile->Enable(ID_CoreWindow_SaveLevel, false);
	menuFile->Enable(ID_CoreWindow_SaveLevelNew, false);
	////////////////////////////////////////////////////////////


	// Edit Dropdown Menu //////////////////////////////////////
	wxMenu *menuEdit = new wxMenu;

	//Edit -> Undo
	wxMenuItem *menuEdit_Undo = new wxMenuItem(menuEdit, ID_CoreWindow_Undo, "&Undo\tCtrl+Z");
	menuEdit_Undo->SetBitmap(wxBITMAP_PNG(UI_ICON_UNDO));
	menuEdit->Append(menuEdit_Undo);

	//Edit -> Redo
	wxMenuItem *menuEdit_Redo = new wxMenuItem(menuEdit, ID_CoreWindow_Redo, "&Redo\tCtrl+Y");
	menuEdit_Redo->SetBitmap(wxBITMAP_PNG(UI_ICON_REDO));
	menuEdit->Append(menuEdit_Redo);

	menuEdit->AppendSeparator();

	//Edit -> Cut
	wxMenuItem *menuEdit_Cut = new wxMenuItem(menuEdit, ID_CoreWindow_Cut, "&Cut\tCtrl+X");
	menuEdit_Cut->SetBitmap(wxBITMAP_PNG(UI_ICON_CUT));
	menuEdit->Append(menuEdit_Cut);

	//Edit -> Copy
	wxMenuItem *menuEdit_Copy = new wxMenuItem(menuEdit, ID_CoreWindow_Copy, "&Copy\tCtrl+C");
	menuEdit_Copy->SetBitmap(wxBITMAP_PNG(UI_ICON_COPY));
	menuEdit->Append(menuEdit_Copy);

	//Edit -> Paste
	wxMenuItem *menuEdit_Paste = new wxMenuItem(menuEdit, ID_CoreWindow_Paste, "&Paste\tCtrl+V");
	menuEdit_Paste->SetBitmap(wxBITMAP_PNG(UI_ICON_PASTE));
	menuEdit->Append(menuEdit_Paste);

	menuEdit->AppendSeparator();

	//Edit -> Delete
	wxMenuItem *menuEdit_Delete = new wxMenuItem(menuEdit, ID_CoreWindow_Delete, "&Delete\tDel");
	menuEdit_Delete->SetBitmap(wxBITMAP_PNG(UI_ICON_DELETE));
	menuEdit->Append(menuEdit_Delete);

	//Edit -> Duplicate
	wxMenuItem *menuEdit_Duplicate = new wxMenuItem(menuEdit, ID_CoreWindow_Duplicate, "&Duplicate\tCtrl+D");
	menuEdit_Duplicate->SetBitmap(wxBITMAP_PNG(UI_ICON_DUPLICATE));
	menuEdit->Append(menuEdit_Duplicate);

	menuEdit->Enable(ID_CoreWindow_Undo, false);
	menuEdit->Enable(ID_CoreWindow_Redo, false);
	menuEdit->Enable(ID_CoreWindow_Cut, false);
	menuEdit->Enable(ID_CoreWindow_Copy, false);
	menuEdit->Enable(ID_CoreWindow_Paste, false);
	menuEdit->Enable(ID_CoreWindow_Delete, false);
	menuEdit->Enable(ID_CoreWindow_Duplicate, false);
	////////////////////////////////////////////////////////////


	// Help Dropdown Menu //////////////////////////////////////
	wxMenu *menuHelp = new wxMenu;

	//Help -> About Pixel Editor...
	wxMenuItem *menuHelp_About = new wxMenuItem(menuHelp, wxID_ABOUT, "&About Pixel Editor...");
	menuHelp_About->SetBitmap(wxBITMAP_PNG(UI_ICON_ABOUT));
	menuHelp->Append(menuHelp_About);
	////////////////////////////////////////////////////////////

	// DevTest Dropdown Menu //////////////////////////////////////
	wxMenu *menuDevTest = new wxMenu;

	//DevTest -> Generate Random Rectangle
	wxMenuItem *menuDevTest_RandomRect = new wxMenuItem(menuDevTest, ID_CoreWindow_DevTest_RandomRect, "&Generate Random Rectangle\tCtrl+T");
	//menuDevTest_RandomRect->SetBitmap(wxBITMAP_PNG(UI_ICON_ABOUT));
	menuDevTest->Append(menuDevTest_RandomRect);
	////////////////////////////////////////////////////////////


	/* Create and append items to menu bar */
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuEdit, "&Edit");
	menuBar->Append(menuHelp, "&Help");
	menuBar->Append(menuDevTest, "&DevTest");
	SetMenuBar(menuBar);

	/* Ribbon bar */
	wxPanel* ribbonBarContainer = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 50));
	wxRibbonBar* ribbonBar = new wxRibbonBar(ribbonBarContainer, wxID_ANY, wxDefaultPosition, ribbonBarContainer->GetSize(),
		wxRIBBON_BAR_FLOW_HORIZONTAL | wxRIBBON_BAR_SHOW_PAGE_LABELS | wxRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS
	);
	ribbonBar->Realize();

	/* Create tools toolbar */
	new Pixel::Editor::ToolsPanel(ribbonBar);
	ribbonBar->Realize();

	/* Create graphics canvas for rendering */
	wxPanel* graphicsCanvasContainer = new wxPanel(this, wxID_ANY, wxPoint(0, 50), wxSize(800, 600));
	new Pixel::Editor::GraphicsCanvas(graphicsCanvasContainer);

	CreateStatusBar();
	SetStatusText("");
}
void Pixel::Editor::CoreWindow::OnFileNew(wxCommandEvent& event)
{
	
}
void Pixel::Editor::CoreWindow::OnFileOpen(wxCommandEvent& event)
{

}
void Pixel::Editor::CoreWindow::OnFileClose(wxCommandEvent& event)
{

}
void Pixel::Editor::CoreWindow::OnFileSave(wxCommandEvent& event)
{

}
void Pixel::Editor::CoreWindow::OnFileSaveAs(wxCommandEvent& event)
{

}
void Pixel::Editor::CoreWindow::OnFileSettings(wxCommandEvent& event)
{

}
void Pixel::Editor::CoreWindow::OnFileExit(wxCommandEvent& event)
{
	Close(true);
}
void Pixel::Editor::CoreWindow::OnHelpAbout(wxCommandEvent & event)
{
	wxMessageBox(
		"Pixel Engine Level Editor\n"
		PIXEL_EDITOR_BUILD_VERSION
	#ifdef PIXEL_EDITOR_IS_DEV_BUILD
		" (dev build)"
	#endif
		"\n\n"
		"Pixel Editor is a level editor created for usage with Pixel Engine. Levels created with "
		"Pixel Editor can be opened, processed, and loaded by Pixel Engine.\n\n"
		"Pixel Editor and Pixel Engine was created and designed by Josh Theriault (@J0shhT)\n\n"
		"Build date: " __DATE__ " @ " __TIME__,
		"About Pixel Editor", wxOK | wxICON_INFORMATION
	);
}

void Pixel::Editor::CoreWindow::OnDevTestRandomRect(wxCommandEvent& event)
{
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_real_distribution<> dist(0, 1);

	auto rectangle = PixelCreateObject(Rectangle);

	rectangle->SetColor(PixelColor(dist(engine), dist(engine), dist(engine)));
	rectangle->SetSize(PixelSize(100.0, 100.0));
	rectangle->SetPosition(PixelWorldPosition(rand() % 700, rand() % 500));
}
