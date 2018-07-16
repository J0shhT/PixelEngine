#pragma once

#include "Include/Common.h"
#include "Include/Type/Position.h"

namespace Pixel::Type
{

	/**
	*  The Pixel::Type::WorldPosition class represents a 2D position in the game world.
	*/
	class PIXEL_API WorldPosition: public Position
	{
		public:

			/**
			*  Class constructor
			*  Creates a new WorldPosition with (x, y) value components set to (0, 0)
			*/
			WorldPosition();

			/**
			*  Class constructor
			*  Creates a new WorldPosition with (x, y) value components set to (xy, xy)
			*/
			WorldPosition(double xy);

			/**
			*  Class constructor
			*  Creates a new WorldPosition with (x, y) value components set to (x, y)
			*/
			WorldPosition(double x, double y);

			/**
			*  Class deconstructor
			*/
			virtual ~WorldPosition();

			/// todo: eventually add methods like WorldPosition to ScreenPosition conversions

	};
}

typedef Pixel::Type::WorldPosition PixelWorldPosition;