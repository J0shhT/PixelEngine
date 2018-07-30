#include "Include/PixelError.h"

#include <SDL/SDL.h>
#include <Windows.h>
#include <tchar.h>

Pixel::Exception::FatalError::FatalError(std::string msg, const unsigned int line, std::string file, std::string func) : _msg(msg), _line(line), _file(file), _func(func)
{
	//Log error to LogService and output
	std::string logMessage = "FATAL ERROR - " + msg;
	Pixel::LogService::Singleton()->Log(this, logMessage);
	Pixel::StandardOut::Singleton()->PrintSilent(Pixel::OutputType::Error, ("FATAL ERROR: " + msg).c_str());

#ifdef _DEBUG
	//Copy error message to Windows Clipboard
	if (OpenClipboard(NULL))
	{
		const size_t len = msg.length() + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), msg.c_str(), len);
		GlobalUnlock(hMem);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}
#endif

	//Display Windows error dialog popup
#ifdef _DEBUG
	std::wstring errorMessageDisplay = std::wstring(L"A fatal error occured and the program needs to quit.\n\n") + 
		std::wstring(msg.begin(), msg.end()) + std::wstring(L"\n\nThe error message has been copied to your clipboard.");
#else
	std::wstring errorMessageDisplay = std::wstring(L"A fatal error occured and the program needs to quit.\n\n");
#endif
	const wchar_t* errorMessageTitle = L"Fatal Error";
	MessageBoxW(NULL,
		LPCTSTR(errorMessageDisplay.c_str()),
		LPCTSTR(errorMessageTitle),
		MB_OK | MB_ICONERROR
	);
}
std::string Pixel::Exception::FatalError::what() const
{
	std::string msg = std::string("Fatal error occured: ") + _msg;
	return msg;
}


Pixel::Error::Error() : Error("An unknown error occured")
{
}
Pixel::Error::Error(std::string msg) : _msg(msg)
{
	//Log error to LogService and output
	std::string logMessage = "ERROR - " + msg;
	Pixel::LogService::Singleton()->Log(this, logMessage);
	Pixel::StandardOut::Singleton()->PrintSilent(Pixel::OutputType::Error, msg.c_str());
}
std::string Pixel::Error::what() const
{
	return _msg;
}


Pixel::Warning::Warning() : Warning("An unknown error occured")
{
}
Pixel::Warning::Warning(std::string msg) : _msg(msg)
{
	//Log warning to LogService and output
	std::string logMessage = "WARNING - " + msg;
	Pixel::LogService::Singleton()->Log(this, logMessage);
	Pixel::StandardOut::Singleton()->PrintSilent(Pixel::OutputType::Warning, msg.c_str());
}
std::string Pixel::Warning::what() const
{
	return _msg;
}