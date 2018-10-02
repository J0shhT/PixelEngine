/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Type/Size.h
*/

#pragma once

#include "Include/Common.h"

namespace Pixel::Type
{

	/**
	*  The Pixel::Type::Size class represents an arbitrary 2D size.
	*/
	class PIXEL_API Size
	{
		public:

			/**
			*  Class constructor
			*  Creates a new Size with (width, height) value components set to (0, 0)
			*/
			Size();

			/**
			*  Class constructor
			*  Creates a new Size with (width, height) value components set to (length, length)
			*/
			Size(double length);

			/**
			*  Class constructor
			*  Creates a new Size with (width, height) value components set to (width, height)
			*/
			Size(double width, double height);

			/**
			*  Class deconstructor
			*/
			virtual ~Size();

			/**
			*  Addition operator overload
			*  This adds the left size components by the right size components
			*/
			Pixel::Type::Size operator+(const Pixel::Type::Size&) const;

			/**
			*  Subtraction operator overload
			*  This subtracts the left size components by the right size components
			*/
			Pixel::Type::Size operator-(const Pixel::Type::Size&) const;

			/**
			*  Multiplication operator overload
			*  This multiplies the left size components by the right size components
			*/
			Pixel::Type::Size operator*(const Pixel::Type::Size&) const;

			/**
			*  Division operator overload
			*  This divides the left size components by the right size components
			*/
			Pixel::Type::Size operator/(const Pixel::Type::Size&) const;

			/**
			*  Unary minus operator overload
			*  This sets the (width, height) value components set to (-width, -height)
			*/
			Pixel::Type::Size operator-() const;

			/**
			*  Equivalence comparison operator overload
			*  This compares if the left size components are equal to the right size components
			*/
			bool operator==(const Pixel::Type::Size&) const;

			/**
			*  Unlike comparison operator overload
			*  This compares if the left size components are *not* equal to the right size components
			*  This is true if the == comparison evaluates to false
			*/
			bool operator!=(const Pixel::Type::Size&) const;

			/**
			*  Greater-than comparison operator overload
			*  This compares if the area of the left is greater than the area of the right
			*/
			bool operator>(const Pixel::Type::Size&) const;

			/**
			*  Greater-than-or-equal-to comparison operator overload
			*  This compares if the area of the left is greater than *or* equal to the area of the right
			*  This is true if the > comparison evaluates to true or the area are equal
			*/
			bool operator>=(const Pixel::Type::Size&) const;

			/**
			*  Less-than comparison operator overload
			*  This compares if the area of the left is less than the area of the right
			*  This is true if the >= comparison evaluates to false
			*/
			bool operator<(const Pixel::Type::Size&) const;

			/**
			*  Less-than-or-equal-to comparison operator overload
			*  This compares if the area of the left is less than *or* equal to the area of the right
			*  This is true if the > comparison comparison evaluates to true
			*/
			bool operator<=(const Pixel::Type::Size&) const;

			/**
			*  Sets the (width, height) value components of this Size to (width, height)
			*/
			void Set(double width, double height);

			/**
			*  Sets the (width, height) value components of this Size to (length, length)
			*/
			void Set(double length);

			/**
			*  Sets the width value component of this Size
			*/
			void SetWidth(double);

			/**
			*  Sets the height value component of this Size
			*/
			void SetHeight(double);

			/**
			*  Returns the width value component of this Size
			*/
			double GetWidth() const;

			/**
			*  Returns the height value component of this Size
			*/
			double GetHeight() const;

			/**
			*  Returns the total area occupied by this Size
			*/
			double GetArea() const;

			/**
			*  Returns a std::string of the (width, height) value components
			*/
			std::string ToString() const;

		private:

			double _width;
			double _height;

	};

}

typedef Pixel::Type::Size PixelSize;