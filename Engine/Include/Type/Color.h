/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Type/Color.h
*/

#pragma once

#include "Include/Common.h"

namespace Pixel::Type
{

	/**
	*  The Pixel::Type::Color class represents a color in normalized RGB format.
	*  RGB values are stored in a normalized format (from 0 - 1).
	*  It is recommended to stick to the 0 - 1 format, but functions are availaible for 0 - 255 format.
	*/
	class PIXEL_API Color
	{
		public:

			/**
			*  Class constructor
			*  Creates a new Color with (red, green, blue) value components set to (0, 0, 0)
			*/
			Color();

			/**
			*  Class constructor
			*  Creates a new Color with (red, green, blue) value components set to (rgb, rgb, rgb)
			*  Values must range from 0 to 1
			*/
			Color(double rgb);

			/**
			*  Class constructor
			*  Creates a new Color with (red, green, blue) value components set to (r, g, b)
			*  Values must range from 0 to 1
			*/
			Color(double r, double g, double b);

			/**
			*  Class constructor
			*  Creates a new Color with (red, green, blue) value components set to (rgb/255, rgb/255, rgb/255)
			*  Values must range from 0 to 255
			*/
			Color(unsigned char rgb);

			/**
			*  Class constructor
			*  Creates a new Color with (red, green, blue) value components set to (r/255, g/255, b/255)
			*  Values must range from 0 to 255
			*/
			Color(unsigned char r, unsigned char g, unsigned char b);

			/**
			*  Class deconstructor
			*/
			virtual ~Color();

			/**
			*  Addition operator overload
			*  This adds the left RGB components by the right RGB components
			*/
			Pixel::Type::Color operator+(const Pixel::Type::Color&) const;

			/**
			*  Subtraction operator overload
			*  This subtracts the left RGB components by the right RGB components
			*/
			Pixel::Type::Color operator-(const Pixel::Type::Color&) const;

			/**
			*  Multiplication operator overload
			*  This multiplies the left RGB components by the right RGB components
			*/
			Pixel::Type::Color operator*(const Pixel::Type::Color&) const;

			/**
			*  Division operator overload
			*  This divides the left RGB components by the right RGB components
			*/
			Pixel::Type::Color operator/(const Pixel::Type::Color&) const;

			/**
			*  Equivalence comparison operator overload
			*  This compares if the left RGB components are equal to the right RGB components
			*/
			bool operator==(const Pixel::Type::Color&) const;

			/**
			*  Unlike comparison operator overload
			*  This compares if the left RGB components are *not* equal to the right RGB components
			*  This is true if the == comparison evaluates to false
			*/
			bool operator!=(const Pixel::Type::Color&) const;

			/**
			*  Greater-than comparison operator overload
			*  This compares if the luminance of the left is greater than the luminance of the right
			*/
			bool operator>(const Pixel::Type::Color&) const;

			/**
			*  Greater-than-or-equal-to comparison operator overload
			*  This compares if the luminance of the left is greater than *or* equal to the luminance of the right
			*  This is true if the > comparison evaluates to true or the luminances are equal
			*/
			bool operator>=(const Pixel::Type::Color&) const;

			/**
			*  Less-than comparison operator overload
			*  This compares if the luminance of the left is less than the luminance of the right
			*  This is true if the >= comparison evaluates to false
			*/
			bool operator<(const Pixel::Type::Color&) const;

			/**
			*  Less-than-or-equal-to comparison operator overload
			*  This compares if the luminance of the left is less than *or* equal to the luminance of the right
			*  This is true if the > comparison evaluates to true
			*/
			bool operator<=(const Pixel::Type::Color&) const;

			/**
			*  Sets the (red, green, blue) value components of this Color to (r, g, b)
			*  Values must range from 0 to 1
			*/
			void Set(double r, double g, double b);

			/**
			*  Sets the (red, green, blue) value components of this Color to (rgb, rgb, rgb)
			*  Values must range from 0 to 1
			*/
			void Set(double rgb);

			/**
			*  Sets the (red, green, blue) value components of this Color to (r/255, g/255, b/255)
			*  Values must range from 0 to 255
			*/
			void Set(unsigned char r, unsigned char g, unsigned char b);

			/**
			*  Sets the (red, green, blue) value components of this Color to (rgb/255, rgb/255, rgb/255)
			*  Values must range from 0 to 255
			*/
			void Set(unsigned char rgb);

			/**
			*  Sets the red value component of this Color
			*  Values must range from 0 to 1
			*/
			void SetRed(double);

			/**
			*  Sets the red value component of this Color
			*  Values must range from 0 to 255
			*/
			void SetRed(unsigned char);

			/**
			*  Sets the green value component of this Color
			*  Values must range from 0 to 1
			*/
			void SetGreen(double);

			/**
			*  Sets the green value component of this Color
			*  Values must range from 0 to 255
			*/
			void SetGreen(unsigned char);

			/**
			*  Sets the blue value component of this Color
			*  Values must range from 0 to 1
			*/
			void SetBlue(double);

			/**
			*  Sets the blue value component of this Color
			*  Values must range from 0 to 255
			*/
			void SetBlue(unsigned char);

			/**
			*  Returns the red value component of this Color
			*/
			double GetRed() const;

			/**
			*  Returns the green value component of this Color
			*/
			double GetGreen() const;

			/**
			*  Returns the blue value component of this Color
			*/
			double GetBlue() const;

			/**
			*  Returns the luminance for this Color using the HSP Color Model formula
			*/
			double GetLuminance() const;

			/**
			*  Returns a std::string of the (red, green, blue) value components
			*/
			std::string ToString() const;

		private:

			double _red;
			double _green;
			double _blue;

	};

}

typedef Pixel::Type::Color PixelColor;