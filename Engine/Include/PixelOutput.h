#pragma once

#include "Common.h"

#define PixelError(msg) Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Error, msg);
#define PixelErrorf(msg, ...) Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Error, msg, __VA_ARGS__);

#define PixelWarn(msg) Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Warning, msg);
#define PixelWarnf(msg, ...) Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Warning, msg, __VA_ARGS__);

#define PixelPrint(msg) Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Message, msg);
#define PixelPrintf(msg, ...) Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Message, msg, __VA_ARGS__);

#define PixelPrintln() Pixel::StandardOut::Singleton()->Println();

namespace Pixel {

	/**
	*  TODO
	*/
	enum class OutputType
	{
		Error, //* Results in red text in the output
		Warning, //* Results in yellow text in the output
		Message, //* Results in white text in the output
		Info, //* Results in blue text in the output
		Debug, //* Results in pink text in the output
	};

	/**
	*  TODO
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

		private:

			/**
			*  For internal use
			*  Changes the text coloring of the console depending
			on the given outputMode
			*/
			void _setupOutput(Pixel::OutputType outputMode);

	};

}