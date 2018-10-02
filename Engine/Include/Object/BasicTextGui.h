/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Object/BasicTextGui.h
*/

#pragma once

#include "Include/Common.h"

#include "GuiObject.h"

#include "Include/Type/Position.h"
#include "Include/Type/Color.h"

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel::Object {

	/**
	*  The Object::BasicTextGui is a gui object used to
	create and display very basic text on the screen.
	*  Only supports Helvetica 18px font.
	*  Text does not wrap.
	*/
	class PIXEL_API BasicTextGui : public GuiObject
	{

		PIXEL_DEFINE_OBJECT(BasicTextGui);

		public:

			/**
			*  Class constructor
			*/
			BasicTextGui();

			/**
			*  Class deconstructor
			*/
			virtual ~BasicTextGui();

			/**
			*  Sets the text to be displayed.
			*/
			void SetText(const std::string&);

			/**
			*  Sets the position where the text will be displayed.
			*  Position is in terms of percentage.
			*  For X: 0.0 is left and 1.0 is right.
			*  For Y: 0.0 is top and 1.0 is bottom.
			*/
			void SetPosition(Pixel::Type::Position);

			/**
			*  Sets the color of the text.
			*/
			void SetTextColor(Pixel::Type::Color);

			/**
			*  Returns the currently displaying text.
			*/
			std::string GetText() const;

			/**
			*  Returns the position the text is being displayed at.
			*/
			Pixel::Type::Position GetPosition() const;

			/**
			*  Returns the current text color.
			*/
			Pixel::Type::Color GetTextColor() const;

			/**
			*  Renders the text on the screen (one frame).
			*/
			void Render();

		protected:

			std::string _text;
			Pixel::Type::Position _position;
			Pixel::Type::Color _textColor;

	};

}

#pragma warning(pop)