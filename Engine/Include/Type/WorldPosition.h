/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Type/WorldPosition.h
*/

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

	};
}

typedef Pixel::Type::WorldPosition PixelWorldPosition;