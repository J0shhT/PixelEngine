/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/SelectionService.h
*/

#pragma once

#include "Include/Common.h"

#include "Include/Object/Object.h"

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  The Pixel::ToolType enum contains the  different types of 
	selection based tools available for the SelectionService.
	*/
	enum class ToolType
	{
		SelectTool, //* The select tool is used to select objects on-screen.
		MoveTool, //* The move tool is used to select+move objects on-screen.
		SizeTool //* The size tool is used to select+resize objects on-screen.
	};

	/**
	*  The Pixel::SelectionService is a singleton service used to
	implement level-editor-like features to game objects such as
	copy, paste, selection, moving, etc
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
			void SetSelection(std::weak_ptr<Pixel::Object::Object>);

			/**
			*  Sets the current selection to nothing.
			*/
			void ResetSelection();

			/**
			*  Returns whether or not there is an object currently selected.
			*/
			bool HasSelection();

			/**
			*  Enables or disables the object selection tool.
			*  When enabled, the user can click on objects to
			set it as the current selection in the SelectionService.
			*/
			void SetSelectToolEnabled(bool enabled = true); ///TODO

			/**
			*  Enables or disables the object move tool.
			*  The object move tool behaves like the Select Tool.
			*  When enabled, the user can click on objects to
			set it as the current selection in the SelectionService.
			*  When an object is selected, it can be moved around using
			move handles on the screen surrounding the object's boundings.
			*/
			void SetMoveToolEnabled(bool enabled = true); ///TODO

			/**
			*  Enables or disables the object sizing tool.
			*  The object sizing tool behaves like the Select Tool.
			*  When enabled, the user can click on objects to
			set it as the current selection in the SelectionService.
			*  When an object is selected, it can be re-sized using sizing 
			handles on the screen surrounding the object's boundings.
			*/
			void SetSizeToolEnabled(bool enabled = true); ///TODO

			/**
			*  Copies the currently selected object to the
			clipboard and then deletes the current selection.
			*/
			//void Cut();

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

		private:

			bool _hasSelection;
			std::weak_ptr<Pixel::Object::Object> _currentSelection;

	};

}

#pragma warning(pop)