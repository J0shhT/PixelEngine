/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/PixelOutput.h
*/

#pragma once

#include "Common.h"

/**
*  Prints the specified message to the output.
*/
#define PixelPrint(msg) Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Message, msg);

/**
*  Prints the specified message format and format variables to the output.
*  Works the same as printf() from the C standard library.
*/
#define PixelPrintf(msg, ...) Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Message, msg, __VA_ARGS__);

/**
*  Prints a blank line to the output.
*/
#define PixelPrintln() Pixel::StandardOut::Singleton()->Println();

namespace Pixel {

	/**
	*  The Pixel::OutputType enum contains all the different types of output.
	*/
	enum class OutputType
	{
		Error, //* For errors -- results in red text in the output
		Warning, //* For warnings -- results in yellow text in the output
		Message, //* For printing normal text -- results in white text in the output
		Info, //* For logging information -- results in blue text in the output
		Debug, //* For temporary debugging - results in pink text in the output
	};

	/**
	*  The Pixel::StandardOut is a singleton class used to manage
	all output to the console of Pixel Engine.

	*  Do not use any printing functions manually such as std::cout
	or printf(), use this service instead.

	*  All output is automatically added to log files unless with
	the exception of the silent functions PrintSilent() and PrintfSilent().
	*/
	class PIXEL_API StandardOut final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::StandardOut);

		public:

			/**
			*  Class constructor
			*/
			StandardOut();

			/**
			*  Class deconstructor
			*/
			~StandardOut();

			/**
			*  Prints the specified message to std::cout and formats the text
			in the console with color depending on what is specified for messageType.
			*  New lines are automatically added at the end of the message.
			*  See StandardOut::Append() for no new lines at the end.
			*/
			void Print(Pixel::OutputType messageType, const char* message);

			/**
			*  Does the same as Print(), but does not log the message to LogService
			*/
			void PrintSilent(Pixel::OutputType messageType, const char* message);

			/**
			*  Prints a blank line to std::cout
			*/
			void Println();

			/**
			*  Prints the specified format formatted with the given additional
			arguments to std::cout and formats the text in the console with color 
			depending on what is specified for messageType.
			*  Prints are limited to 2048 characters with this function.
			*  New lines are automatically added at the end of the message.
			*  See StandardOut::Appendf() for no new lines at the end.
			*/
			void Printf(Pixel::OutputType messageType, const char* format, ...);

			/**
			*  Does the same as Printf(), but does not log the message to LogService
			*/
			void PrintfSilent(Pixel::OutputType messageType, const char* format, ...);

		private:

			void _setupOutput(Pixel::OutputType outputMode);

	};

}