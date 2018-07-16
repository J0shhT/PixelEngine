#include "Include/PixelError.h"

#include <SDL/SDL.h>
#include <Windows.h>
#include <tchar.h>

Pixel::Exception::RuntimeError::RuntimeError(std::string msg) : std::exception(msg.c_str()), _msg(msg)
{
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
	//Display Windows error dialog popup
	std::wstring errorMessageDisplay = std::wstring(L"An error occured in the program.\n\n") +
		std::wstring(msg.begin(), msg.end()) + std::wstring(L"\n\nThe error message has been copied to your clipboard.");
	const wchar_t* errorMessageTitle = L"Runtime Error";
	MessageBoxW(NULL,
		LPCTSTR(errorMessageDisplay.c_str()),
		LPCTSTR(errorMessageTitle),
		MB_OK | MB_ICONWARNING
	);
}
const char* Pixel::Exception::RuntimeError::what() const
{
	std::string msg;
	msg = std::string("Runtime error occured: ") + std::string(_msg);
	return msg.c_str();
}


Pixel::Exception::FatalError::FatalError(std::string msg) : std::exception(msg.c_str()), _msg(msg)
{
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
	//Display Windows error dialog popup
	std::wstring errorMessageDisplay = std::wstring(L"A fatal error occured and the program needs to quit.\n\n") + 
		std::wstring(msg.begin(), msg.end()) + std::wstring(L"\n\nThe error message has been copied to your clipboard.");
	const wchar_t* errorMessageTitle = L"Fatal Error";
	MessageBoxW(NULL,
		LPCTSTR(errorMessageDisplay.c_str()),
		LPCTSTR(errorMessageTitle),
		MB_OK | MB_ICONERROR
	);
}
const char* Pixel::Exception::FatalError::what() const
{
	std::string msg = std::string("Fatal error occured: ") + _msg;
	const char* msg_c = msg.c_str();
	return msg_c;
}