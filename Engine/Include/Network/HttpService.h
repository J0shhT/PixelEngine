/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Network/HttpService.h
*/

#pragma once

#include "Include/Common.h"

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  The Pixel::HttpResponse struct represents and contains a response from a web server.
	*/
	struct HttpResponse
	{
		bool success; //* Set to true if the request was a success
		std::map<std::string, std::string> headers; //* The response headers from the server (stored as key-value pairs)
		std::string rawHeaders; //* The raw response headers from the server
		std::string body; //* The response body content from the server
		unsigned short statusCode; //* The HTTP status code responded by the server
	};

	/**
	*  The Pixel::HttpService is a singleton service used to send
	HTTP requests to outside servers or websites.
	*  Currently only supports GET and POST.
	*  Supports SSL (https).
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
			*  Sends an HTTP GET request to the specified url, and returns the response.
			*/
			Pixel::HttpResponse Get(std::string url);

			/**
			*  Sends an HTTP POST request to the specified url, and returns the response.
			*  Data is sent in application/x-www-form-urlencoded format (ex: "Hello=World&Test=123")
			*/
			Pixel::HttpResponse Post(std::string url, std::string &data);

		private:

			static size_t _curlDataWriteCallback(char* buf, size_t size, size_t nmemb, void* userp);

	};

}

#pragma warning(pop)