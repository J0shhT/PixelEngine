#pragma once

#define PIXEL_ENGINE
#define PIXEL_ENGINE_VERSION "1.0.0.0"

//DLL export/import defines

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <memory.h>
#include <stdarg.h>

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
	SetConsoleTextAttribute(consoleHandle, 11); \
	std::ostringstream __creationMessage; \
	__creationMessage << STRINGIFY(className) "() - Created " << this; \
	std::cout << __creationMessage.str() << std::endl; \
	Pixel::LogService::Singleton()->Log(this, __creationMessage.str()); \
	SetConsoleTextAttribute(consoleHandle, 15);

#define PIXEL_SINGLETON_DECONSTRUCTOR(className) \
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); \
	SetConsoleTextAttribute(consoleHandle, 11); \
	std::ostringstream __creationMessage; \
	__creationMessage << STRINGIFY(className) "() - Destroyed " << this; \
	std::cout << __creationMessage.str() << std::endl; \
	Pixel::LogService::Singleton()->Log(this, __creationMessage.str()); \
	SetConsoleTextAttribute(consoleHandle, 15); \
	className::instance = nullptr;