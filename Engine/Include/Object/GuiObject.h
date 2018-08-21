#pragma once

#include "Include/Common.h"

#include "RenderableObject.h"

namespace Pixel::Object {

	/**
	*  TODO
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
			*  TODO
			*/
			void SetVisible(bool);

			/**
			*  TODO
			*/
			bool IsVisible() const;

		protected:

			bool _isVisible;

	};

}