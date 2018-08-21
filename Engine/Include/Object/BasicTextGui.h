#pragma once

#include "Include/Common.h"

#include "GuiObject.h"

#include "Include/Type/Position.h"
#include "Include/Type/Color.h"

namespace Pixel::Object {

	/**
	*  TODO
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
			*  TODO
			*/
			void SetText(const std::string&);

			/**
			*  TODO
			*/
			void SetPosition(Pixel::Type::Position);

			/**
			*  TODO
			*/
			void SetTextColor(Pixel::Type::Color);

			/**
			*  TODO
			*/
			std::string GetText() const;

			/**
			*  TODO
			*/
			Pixel::Type::Position GetPosition() const;

			/**
			*  TODO
			*/
			Pixel::Type::Color GetTextColor() const;

			/**
			*  TODO
			*/
			void Render();

		protected:

			std::string _text;
			Pixel::Type::Position _position;
			Pixel::Type::Color _textColor;

	};

}