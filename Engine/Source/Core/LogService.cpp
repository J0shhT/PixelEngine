/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Core/LogService.cpp
*/

#include "Include/Core/LogService.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

#include "Include/PixelError.h"

#define UNIQUE_LOG_FILES

PIXEL_DECLARE_AUTOSINGLETON(Pixel::LogService);

Pixel::LogService::LogService()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::LogService);
	_enableNormalLogReporting = false;
}

Pixel::LogService::~LogService()
{
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::LogService);
}

void Pixel::LogService::UploadLogs(Pixel::LogType logType)
{
#ifdef UNIQUE_LOG_FILES
	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count();
	std::string logGuid = std::to_string(timestamp);
#else
	std::string logGuid = "PixelEngine";
#endif
	std::string file;
	switch (logType)
	{
		case Pixel::LogType::CrashLog:
			file = "Logs/" + logGuid + "_crash.log";
			break;
		default:
			file = "Logs/" + logGuid + ".log";
	}

	std::ofstream logFile;
	logFile.open(file, std::fstream::out);

	if (logFile.is_open())
	{
		logFile << "Pixel Engine Log File\n";
		logFile << "Engine Version: " PIXEL_ENGINE_VERSION "\n";
		logFile << "Engine Build Date: " __DATE__ " @ " __TIME__ "\n";
		logFile << "\n";

		for (auto iter = _logs.cbegin(); iter != _logs.cend(); iter++)
		{
			logFile << (*iter);
			logFile << "\n";
		}

		logFile.close();
	}
}

void Pixel::LogService::Log(void* caller, const std::string &message)
{
	std::ostringstream log;

	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count();

	//Log Timestamp
	log << timestamp;
	log << ",";

	//Log caller
	if (caller == nullptr)
	{
		log << "00000000";
	}
	else
	{
		log << caller;
	}
	log << " >> ";

	//Log message
	log << message;

	_logs.push_back(log.str());
}

void Pixel::LogService::Log(const std::string &message)
{
	Log(nullptr, message);
}

void Pixel::LogService::SetNormalLogReportingEnabled(bool value)
{
	_enableNormalLogReporting = value;
}

bool Pixel::LogService::IsNormalLogReportingEnabled() const
{
	return _enableNormalLogReporting;
}
