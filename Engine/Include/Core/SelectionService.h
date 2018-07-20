#pragma once

#include "Include/Common.h"

namespace Pixel {

	/**
	*  The different types of selection based tools in Pixel Engine.
	*/
	enum ToolType
	{
		SelectTool, //* The select tool is used to select objects on-screen.
		MoveTool, //* The move tool is used to select+move objects on-screen.
		SizeTool //* The size tool is used to select+resize objects on-screen.
	};

	/**
	*  TODO
	*/
	class PIXEL_API SelectionService final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::SelectionService);

		public:

			/**
			*  Class constructor
			*/
			SelectionService();

			/**
			*  Class deconstructor
			*/
			~SelectionService();

			/**
			*  Sets the current selection manually for the SelectionService.
			*/
			void SetSelection(void); ///TODO

			/**
			*  Enables or disables the object selection tool.
			*  When enabled, the user can click on objects to
			set it as the current selection in the SelectionService.
			*/
			void EnableSelectTool(bool enabled = true); ///TODO

			/**
			*  Enables or disables the object move tool.
			*  The object move tool behaves like the Select Tool.
			*  When enabled, the user can click on objects to
			set it as the current selection in the SelectionService.
			*  When an object is selected, it can be moved around using
			move handles on the screen surrounding the object's boundings.
			*/
			void EnableMoveTool(bool enabled = true); ///TODO

			/**
			*  Enables or disables the object sizing tool.
			*  The object sizing tool behaves like the Select Tool.
			*  When enabled, the user can click on objects to
			set it as the current selection in the SelectionService.
			*  When an object is selected, it can be re-sized using sizing 
			handles on the screen surrounding the object's boundings.
			*/
			void EnableSizeTool(bool enabled = true); ///TODO

			/**
			*  Deletes the currently selected object and copies
			it to the clipboard for pasting.
			*/
			void Cut(); ///TODO

			/**
			*  Copies the currently selected object to the
			clipboard for pasting.
			*/
			void Copy(); ///TODO

			/**
			*  Pastes the object that is currently on the clipboard.
			*/
			void Paste(); ///TODO

			/**
			*  Deletes the currently selected object.
			*/
			void Delete(); ///TODO

			/**
			*  Creates a duplicate of the currently selected object.
			*  This function is the same as copy and pasting.
			*/
			void Duplicate(); ///TODO
	};

}