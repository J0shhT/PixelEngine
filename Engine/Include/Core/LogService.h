/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/LogService.h
*/

#pragma once

#include "Include/Common.h"

/**
*  This macro logs a message to the LogService under the specified object
*  Argument 1: A pointer to the object logging this message
*  Argument 2: The message to log
*/
#define PixelLog(p, msg) Pixel::LogService::Singleton()->Log((void*)p, msg);

/**
*  This macro logs a message to the LogService
*  Argument 1: The message to log
*/
#define PixelLogMsg(msg) Pixel::LogService::Singleton()->Log(msg);

/**
*  This macro logs a message to the LogService under the current object
*  Argument 1: The message to log
*/
#define PixelLogThis(msg) Pixel::LogService::Singleton()->Log((void*)this, msg);

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  The Pixel::LogType enum contains the different types of
	log files that the LogService can create.
	*/
	enum class LogType
	{
		NormalLog,
		CrashLog
	};

	/**
	*  The Pixel::LogService is a singleton service used to log
	messages to be added to a log file during a crash and/or after
	the program exits for debugging purposes.
	
	*  Messages that are printed via Pixel::StandardOut automatically
	log to the LogService.

	*  This service should be used when you need to manually log a message
	for log files for debugging.
	*/
	class PIXEL_API LogService final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::LogService);

		public:

			/**
			*  Class constructor
			*/
			LogService();

			/**
			*  Class deconstructor
			*/
			~LogService();

			/**
			*  Logs all the currently added messages to a log file.
			*  Log files are created in the "Logs" folder where the executable
			is running from. This folder must exist for logs to be created.
			*  The names of log files are UNIX timestamps of when they were generated.
			*  Log files that were generated due to a crash will have "_crash" at the
			end of their file name.
			*/
			void UploadLogs(Pixel::LogType logType = Pixel::LogType::NormalLog);

			/**
			*  Logs the specified message under the specified caller.
			*  The caller is used to debug where the log is being added from.
			*  The caller's memory address is added in the log file before the message.
			*/
			void Log(void* caller, const std::string &message);

			/**
			*  Logs the specified message.
			*/
			void Log(const std::string &message);

			/**
			*  Sets whether or not log files should be created everytime
			the program exits. Defaults to false.
			*/
			void SetNormalLogReportingEnabled(bool);

			/**
			*  Returns whether or not normal log reporting is enabled.
			*  See LogService::SetNormalLogReportingEnabled()
			*/
			bool IsNormalLogReportingEnabled() const;

		private:

			std::vector<std::string> _logs;
			bool _enableNormalLogReporting;

	};

}

#pragma warning(pop)