#pragma once

#include "Include/Common.h"

namespace Pixel {

	/**
	*  Represents and contains a response from a web server
	*/
#pragma warning(push)
#pragma warning(disable: 4251)
	struct PIXEL_API HttpResponse
	{
		bool success; //* Set to true if the request was a success
		std::map<std::string, std::string> headers; //* The response headers from the server (stored as key-value pairs)
		std::string rawHeaders; //* The raw response headers from the server
		std::string body; //* The response body content from the server
		unsigned short statusCode; //* The HTTP status code responded by the server
	};

	/**
	*  Contains specific information relating to a URL
	*  See Pixel::HttpService::GetInformationFromURL()
	*/
	struct PIXEL_API URL
	{
		std::string protocol;
		std::string domain;
		std::string path;
		std::string parameters;
		bool isValid;
	};
#pragma warning(pop)

	/**
	*  TODO
	*/
	class PIXEL_API HttpService
	{
		public:

			/**
			*  Class constructor
			*  This function can throw a Pixel::Exception::FatalError
			*/
			HttpService();

			/**
			*  Class deconstructor
			*/
			virtual ~HttpService();

			/**
			*  Class singleton getter
			*  This function can throw a Pixel::Exception::FatalError
			*/
			static Pixel::HttpService* Singleton();

			/**
			*  TODO
			*/
			Pixel::URL GetInformationFromURL(std::string url);

			/**
			*  Sends an HTTP GET request to the specified url
			*/
			Pixel::HttpResponse Get(std::string url);

			/**
			*  Sends an HTTP POST request to the specified url
			*  Data is sent in application/x-www-form-urlencoded format (ex: "Hello=World&Test=123")
			*/
			Pixel::HttpResponse Post(std::string url, std::string &data);

		private:

			/**
			*  The singleton instance for this class (only one Pixel:HttpService can exist)
			*  See Pixel::HttpService::Singleton()
			*/
			static Pixel::HttpService* instance;

			/**
			*  Internal usage only
			*/
			static size_t _curlDataWriteCallback(char* buf, size_t size, size_t nmemb, void* userp);
		};

}