#pragma once

#include "Include/Common.h"

#include "Include/Core/LogService.h"
#include "Include/PixelOutput.h"

#define	PIXEL_SUCCESS			0x0
#define	PIXEL_ERROR				0x1
#define	PIXEL_ERROR_UNKNOWN		0x2

#pragma warning(push)
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

namespace Pixel::Exception {

	class PIXEL_API FatalError
	{
		public:
			FatalError(std::string msg, const unsigned int line = 0u, std::string file = "Unknown", std::string func = "Unknown");
			std::string what() const;
		private:
			std::string _msg;
			const unsigned int _line;
			std::string _file;
			std::string _func;
	};

}

namespace Pixel {

	class PIXEL_API Error
	{
		public:
			Error();
			Error(std::string msg);
			std::string what() const;
		private:
			std::string _msg;
	};

	class PIXEL_API Warning
	{
		public:
			Warning();
			Warning(std::string msg);
			std::string what() const;
		private:
			std::string _msg;
	};

}

#pragma warning(pop)

#define PixelFatalError(msg) throw Pixel::Exception::FatalError(msg, __LINE__, __FILE__, __FUNCTION__);
#define PixelError(msg) Pixel::Error(msg);
#define PixelWarning(msg) Pixel::Warning(msg);