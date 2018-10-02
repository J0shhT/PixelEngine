/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Object/Rectangle.h
*/

#pragma once

#include "Include/Common.h"

#include "PhysicalObject.h"

namespace Pixel::Object {

	/**
	*  The Object::Rectangle is a physical game object
	that takes the form of a rectangle.
	*  Rectangles are made from 2 triangles (6 verticies).
	*/
	class PIXEL_API Rectangle : public PhysicalObject
	{

		PIXEL_DEFINE_OBJECT(Rectangle);

		public:

			/**
			*  Class constructor
			*/
			Rectangle();

			/**
			*  Class deconstructor
			*/
			virtual ~Rectangle();

			/**
			*  Steps through one physics frame of this rectangle.
			*/
			void StepPhysics(double frameDelta);

			/**
			*  Renders one frame of this rectangle.
			*/
			void Render();

		protected:

			void _checkCollisions();

	};

}