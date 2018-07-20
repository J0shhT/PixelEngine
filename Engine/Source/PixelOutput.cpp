#include "Include/PixelOutput.h"

#include "Include/PixelError.h"

PIXEL_DECLARE_AUTOSINGLETON(Pixel::StandardOut);

Pixel::StandardOut::StandardOut()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::StandardOut);
}

Pixel::StandardOut::~StandardOut()
{
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::StandardOut);
}

void Pixel::StandardOut::Append(Pixel::OutputType messageType, const char* message)
{
	_setupOutput(messageType);
	std::cout << message;
	_setupOutput(Pixel::OutputType::Message);
}

void Pixel::StandardOut::Print(Pixel::OutputType messageType, const char* message)
{
	Append(messageType, message);
	Println();
}

void Pixel::StandardOut::Println()
{
	std::cout << std::endl;
}

void Pixel::StandardOut::Appendf(Pixel::OutputType messageType, const char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	char buffer[2048];
	vsprintf(buffer, format, argptr);

	_setupOutput(messageType);
	std::cout << buffer;
	_setupOutput(Pixel::OutputType::Message);

	va_end(argptr);
}

void Pixel::StandardOut::Printf(Pixel::OutputType messageType, const char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	char buffer[2048];
	vsprintf(buffer, format, argptr);

	_setupOutput(messageType);
	std::cout << buffer << std::endl;
	_setupOutput(Pixel::OutputType::Message);

	va_end(argptr);
}

void Pixel::StandardOut::_setupOutput(Pixel::OutputType mode)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (mode)
	{
		case Pixel::OutputType::Warning:
			SetConsoleTextAttribute(consoleHandle, 14);
			break;
		case Pixel::OutputType::Error:
			SetConsoleTextAttribute(consoleHandle, 12);
			break;
		case Pixel::OutputType::Debug:
			SetConsoleTextAttribute(consoleHandle, 13);
			break;
		case Pixel::OutputType::Info:
			SetConsoleTextAttribute(consoleHandle, 11);
			break;
		default:
			SetConsoleTextAttribute(consoleHandle, 15);
			break;
	}
}