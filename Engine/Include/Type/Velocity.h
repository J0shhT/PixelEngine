#pragma once

#include "Include/Common.h"
#include "Include/Type/Position.h"

namespace Pixel::Type
{

	/**
	*  The Pixel::Type::Velocity class represents a 2D velocity force.
	*/
	class PIXEL_API Velocity : public Position
	{
		public:

			/**
			*  Class constructor
			*  Creates a new Velocity with (x, y) value components set to (0, 0)
			*/
			Velocity();

			/**
			*  Class constructor
			*  Creates a new Velocity with (x, y) value components set to (xy, xy)
			*/
			Velocity(double xy);

			/**
			*  Class constructor
			*  Creates a new Velocity with (x, y) value components set to (x, y)
			*/
			Velocity(double x, double y);

			/**
			*  Class deconstructor
			*/
			virtual ~Velocity();

	};
}

typedef Pixel::Type::Velocity PixelVelocity;