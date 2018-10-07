/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Common.h
*/

#pragma once

#define PIXEL_ENGINE
#define PIXEL_ENGINE_BUILD "alpha"
#define PIXEL_ENGINE_VERSION "0.1.1.0"
#define PIXEL_ENGINE_VERSION_INTERNAL "0.1.1.0"

#define DEBUG_BUILD_FILE_DIR "J:/PixelEngine/Dev/Release/"

/* DLL import/export defines */
#ifdef DLL_EXPORTS
	#define PIXEL_API __declspec(dllexport)
#else
	#define PIXEL_API __declspec(dllimport)
#endif

/* C++ Libraries */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>
#include <exception>
#include <stdexcept>
#include <algorithm>

/* C Libraries */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <ctime>
#include <memory.h>
#include <cstdarg>

/* Windows API */
#include <Windows.h>

/* Macros */

#define CONCAT(a, b) a##b
#define CONCAT3(a, b, c) CONCAT(a, b)##c
#define CONCAT4(a, b, c, d) CONCAT3(a, b, c)##d
#define STRINGIFY(x) #x
#define WIDEN(x) CONCAT(L, STRINGIFY(x))

/* Singleton macros */

#define PIXEL_DEFINE_SINGLETON(className) \
	public: \
		static className* Singleton(); \
	private: \
		static className* instance;

#define PIXEL_DECLARE_SINGLETON(className) \
	className* className::instance = nullptr; \
	className* className::Singleton() \
	{ \
		assert(className::instance != nullptr); \
		if (className::instance == nullptr) \
			throw Pixel::Exception::FatalError("Failed to get " STRINGIFY(className) " singleton because instance does not exist"); \
		return className::instance; \
	}

#define PIXEL_DECLARE_AUTOSINGLETON(className) \
	className* className::instance = nullptr; \
	className* className::Singleton() \
	{ \
		if (className::instance == nullptr) \
			new className(); \
		return className::instance; \
	}

#define PIXEL_SINGLETON_CONSTRUCTOR(className) \
	assert(className::instance == nullptr); \
	if (className::instance != nullptr) \
		throw Pixel::Exception::FatalError("Failed to create " STRINGIFY(className) " because a singleton instance already exists"); \
	className::instance = this; \
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); \
	SetConsoleTextAttribute(consoleHandle, 13); \
	std::ostringstream __creationMessage; \
	__creationMessage << STRINGIFY(className) "() - Created " << this; \
	std::cout << __creationMessage.str() << std::endl; \
	Pixel::LogService::Singleton()->Log(this, __creationMessage.str()); \
	SetConsoleTextAttribute(consoleHandle, 15);

#define PIXEL_SINGLETON_DECONSTRUCTOR(className) \
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); \
	SetConsoleTextAttribute(consoleHandle, 13); \
	std::ostringstream __creationMessage; \
	__creationMessage << STRINGIFY(className) "() - Destroyed " << this; \
	std::cout << __creationMessage.str() << std::endl; \
	Pixel::LogService::Singleton()->Log(this, __creationMessage.str()); \
	SetConsoleTextAttribute(consoleHandle, 15); \
	className::instance = nullptr;

/* Helper functions */
namespace Pixel::Util
{

	template <typename T>
	inline bool IsWeakPtrInitialized(std::weak_ptr<T> const& weak)
	{
		return !(!weak.owner_before(std::weak_ptr<T>{}) && !std::weak_ptr<T>{}.owner_before(weak));
	}

}