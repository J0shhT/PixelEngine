#pragma once

#include "Include/Common.h"

#define PixelLog(p, msg) Pixel::LogService::Singleton()->Log((void*)p, msg);
#define PixelLogMsg(msg) Pixel::LogService::Singleton()->Log(msg);
#define PixelLogThis(msg) Pixel::LogService::Singleton()->Log((void*)this, msg);

namespace Pixel {

	enum LogType
	{
		NormalLog,
		CrashLog
	};

	/**
	*  TODO
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
			*  TODO
			*/
			void UploadLogs(Pixel::LogType logType = Pixel::LogType::NormalLog);

			/**
			*  TODO
			*/
			void Log(void* caller, const std::string &message);

			/**
			*  TODO
			*/
			void Log(const std::string &message);

		private:

			std::vector<std::string> _logs;


	};

}