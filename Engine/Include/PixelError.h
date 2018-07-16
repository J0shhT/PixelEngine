#pragma once

#include "Include/Common.h"

#define	PIXEL_SUCCESS			0x0
#define	PIXEL_ERROR				0x1
#define	PIXEL_ERROR_UNKNOWN		0x2

#pragma warning(push)
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

namespace Pixel::Exception {

	class PIXEL_API RuntimeError : public std::exception
	{
		public:
			RuntimeError(std::string msg);
			const char* what() const;
		private:
			std::string _msg;
	};

	class PIXEL_API FatalError : public std::exception
	{
		public:
			FatalError(std::string msg);
			const char* what() const;
		private:
			std::string _msg;
	};

}

#pragma warning(pop)