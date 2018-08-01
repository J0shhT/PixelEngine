#pragma once

#include "Include/Common.h"

#include "PhysicalObject.h"

namespace Pixel::Object {

	/**
	*  TODO
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
			*  TODO
			*/
			void StepPhysics(double frameDelta);

			/**
			*  TODO
			*/
			void Render();

		protected:

			void _checkCollisions();

	};

}