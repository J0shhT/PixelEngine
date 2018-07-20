#pragma once

#include "Include/Common.h"

namespace Pixel {

#pragma warning(push)
#pragma warning(disable: 4251)
	/**
	*  Represents and contains a response from a web server
	*/
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
	class PIXEL_API HttpService final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::HttpService);

		public:

			/**
			*  Class constructor
			*/
			HttpService();

			/**
			*  Class deconstructor
			*/
			~HttpService();

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
			*  Internal usage only
			*/
			static size_t _curlDataWriteCallback(char* buf, size_t size, size_t nmemb, void* userp);
		};

}