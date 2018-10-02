/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Object/GuiObject.h
*/

#pragma once

#include "Include/Common.h"

#include "RenderableObject.h"

namespace Pixel::Object {

	/**
	*  The Object::GuiObject is an abstract class used 
	to represent a gui object in Pixel Engine.
	*  All gui related objects inherit from this class.
	*/
	class PIXEL_API GuiObject : public RenderableObject
	{

		PIXEL_DEFINE_OBJECT(GuiObject);

		public:

			/**
			*  Class constructor
			*/
			GuiObject();

			/**
			*  Class deconstructor
			*/
			virtual ~GuiObject();

			/**
			*  Sets whether or not the gui object is visible.
			*  Setting this to false makes the gui object not render.
			*/
			void SetVisible(bool);

			/**
			*  Returns whether or not the gui object is visible.
			*/
			bool IsVisible() const;

			/**
			*  Abstract function to render the gui object.
			*/
			void Render() = 0;

		protected:

			bool _isVisible;

	};

}