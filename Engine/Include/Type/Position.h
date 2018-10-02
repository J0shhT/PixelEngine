/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Type/Position.h
*/

#pragma once

#include "Include/Common.h"

namespace Pixel::Type
{

	/**
	*  The Pixel::Type::Position class represents an arbitrary 2D position.
	*/
	class PIXEL_API Position
	{
		public:

			/**
			*  Class constructor
			*  Creates a new Position with (x, y) value components set to (0, 0)
			*/
			Position();

			/**
			*  Class constructor
			*  Creates a new Position with (x, y) value components set to (xy, xy)
			*/
			Position(double xy);

			/**
			*  Class constructor
			*  Creates a new Position with (x, y) value components set to (x, y)
			*/
			Position(double x, double y);

			/**
			*  Class deconstructor
			*/
			virtual ~Position();

			/**
			*  Addition operator overload
			*  This adds the left XY components by the right XY components
			*/
			Pixel::Type::Position operator+(const Pixel::Type::Position&) const;

			/**
			*  Subtraction operator overload
			*  This subtracts the left XY components by the right XY components
			*/
			Pixel::Type::Position operator-(const Pixel::Type::Position&) const;

			/**
			*  Multiplication operator overload
			*  This multiplies the left XY components by the right XY components
			*/
			Pixel::Type::Position operator*(const Pixel::Type::Position&) const;

			/**
			*  Division operator overload
			*  This divides the left XY components by the right XY components
			*/
			Pixel::Type::Position operator/(const Pixel::Type::Position&) const;

			/**
			*  Unary minus operator overload
			*  This sets the (x, y) value components set to (-x, -y)
			*/
			Pixel::Type::Position operator-() const;

			/**
			*  Equivalence comparison operator overload
			*  This compares if the left XY components are equal to the right XY components
			*/
			bool operator==(const Pixel::Type::Position&) const;

			/**
			*  Unlike comparison operator overload
			*  This compares if the left XY components are *not* equal to the right XY components
			*  This is true if the == comparison evaluates to false
			*/
			bool operator!=(const Pixel::Type::Position&) const;

			/**
			*  Greater-than comparison operator overload
			*  This compares if the magnitude of the left is greater than the magnitude of the right
			*/
			bool operator>(const Pixel::Type::Position&) const;

			/**
			*  Greater-than-or-equal-to comparison operator overload
			*  This compares if the magnitude of the left is greater than *or* equal to the magnitude of the right
			*  This is true if the > comparison evaluates to true or the magnitudes are equal
			*/
			bool operator>=(const Pixel::Type::Position&) const;

			/**
			*  Less-than comparison operator overload
			*  This compares if the magnitude of the left is less than the magnitude of the right
			*  This is true if the >= comparison evaluates to false
			*/
			bool operator<(const Pixel::Type::Position&) const;

			/**
			*  Less-than-or-equal-to comparison operator overload
			*  This compares if the magnitude of the left is less than *or* equal to the magnitude of the right
			*  This is true if the > comparison evaluates to true
			*/
			bool operator<=(const Pixel::Type::Position&) const;

			/**
			*  Sets the (x, y) value components of this Position to (x, y)
			*/
			void Set(double x, double y);

			/**
			*  Sets the (x, y) value components of this Position to (xy, xy)
			*/
			void Set(double xy);

			/**
			*  Sets the x value component of this Position
			*/
			void SetX(double);

			/**
			*  Sets the y value component of this Position
			*/
			void SetY(double);

			/**
			*  Returns the x value component of this Position
			*/
			double GetX() const;

			/**
			*  Returns the y value component of this Position
			*/
			double GetY() const;

			/**
			*  Returns the total area occupied by this Position
			*  This is equal x * y
			*/
			double GetArea() const;

			/**
			*  Returns the magnitude (total length) of this Position
			*  This is equal to sqrt(x * x + y * y)
			*/
			double GetMagnitude() const;

			/**
			*  Returns the angle formed by the x and y components relative to the x axis
			*  This is equal to the tangent of y/x
			*  The angle returned is in radians, unless inDegrees is set to true
			*/
			double GetAngle(bool inDegrees = false) const;

			/**
			*  Returns a std::string of the (x, y) value components
			*/
			std::string ToString() const;

		private:

			double _x;
			double _y;

	};

}

typedef Pixel::Type::Position PixelPosition;