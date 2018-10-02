/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/PixelError.h
*/

#pragma once

#include "Include/Common.h"

#include "PixelOutput.h"

#include "Include/Core/LogService.h"

/**
*  Throws a Pixel::Exception::FatalError exception with the specified message.
*  This macro should be used instead of manually using the FatalError class.
*  This macro automatically fills in the line, file, and function of where it was called.
*/
#define PixelFatalError(msg) throw Pixel::Exception::FatalError(msg, __LINE__, __FILE__, __FUNCTION__);

/**
*  Raises a Pixel::Error with the specified message to the console and logs.
*/
#define PixelError(msg) Pixel::Error(msg);

/**
*  Raises a Pixel::Warning with the specified message to the console and logs.
*/
#define PixelWarning(msg) Pixel::Warning(msg);

#pragma warning(push)
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

namespace Pixel::Exception {

	/**
	*  The Exception::FatalError class is used to raise
	fatal Pixel Engine related exceptions.

	*  You should use the PixelFatalError() macro instead of
	using this class manually.

	*  This exception will never full throw all the way through
	your program if you are using PixelMain(): this is intended.

	*  You may catch this exception inside of your main function
	passed to the PixelMain() macro to prevent a crash.

	*  If this exception escapes outside of the main function
	passed to the PixelMain() macro, it will be caught internally
	by PixelMain() and Pixel Engine will forcefully crash and will 
	cause the program to quit, display an error message, and generate
	a crash log in the Logs folder of the application.
	*/
	class PIXEL_API FatalError
	{
		public:

			/**
			*  Class constructor
			*/
			FatalError(std::string msg, const unsigned int line = 0u, std::string file = "Unknown", std::string func = "Unknown");

			/**
			*  Returns formatted information message about the exception.
			*/
			std::string what() const;

		private:

			std::string _msg;
			const unsigned int _line;
			std::string _file;
			std::string _func;

	};

}

namespace Pixel {

	/**
	*  The Pixel::Error class is used to raise errors in the console 
	and logs of Pixel Engine.
	*  These errors do not crash the program and are for debugging.
	*/
	class PIXEL_API Error
	{
		public:

			/**
			*  Class constructor
			*/
			Error();

			/**
			*  Class constructor
			*/
			Error(std::string msg);

			/**
			*  Returns the error message for this error.
			*/
			std::string what() const;

		private:

			std::string _msg;

	};

	/**
	*  The Pixel::Warning class is used to raise warnings in the console 
	and logs of Pixel Engine.
	*  These warnings do not crash the program and are for debugging.
	*  Warnings are the same as errors except they appear as yellow
	in the console and are marked as a warning in the logs.
	*/
	class PIXEL_API Warning
	{
		public:

			/**
			*  Class constructor
			*/
			Warning();

			/**
			*  Class constructor
			*/
			Warning(std::string msg);

			/**
			*  Returns the warning message for this warning.
			*/
			std::string what() const;

		private:

			std::string _msg;

	};

}

#pragma warning(pop)