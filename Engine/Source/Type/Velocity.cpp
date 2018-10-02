/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Type/Velocity.cpp
*/

#include "Include/Type/Velocity.h"

Pixel::Type::Velocity::Velocity() : Pixel::Type::Position()
{
}

Pixel::Type::Velocity::Velocity(double xy) : Pixel::Type::Position(xy)
{
}

Pixel::Type::Velocity::Velocity(double x, double y) : Pixel::Type::Position(x, y)
{
}

Pixel::Type::Velocity::~Velocity()
{
}