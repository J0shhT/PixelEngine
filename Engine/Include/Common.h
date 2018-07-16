#pragma once

//DLL export/import defines
#ifdef DLL_EXPORTS
	#define PIXEL_API __declspec(dllexport)
#else
	#define PIXEL_API __declspec(dllimport)
#endif

//C++ Libraries
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

//C Libraries
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <memory.h>