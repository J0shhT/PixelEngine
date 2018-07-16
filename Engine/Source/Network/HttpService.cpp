#include "Include/Network/HttpService.h"

#include "Include/PixelError.h"

#include <regex>
#include <curl/curl.h>

Pixel::HttpService::HttpService()
{
	assert(Pixel::HttpService::instance == nullptr);
	if (Pixel::HttpService::instance != nullptr)
		throw Pixel::Exception::FatalError("Failed to create Pixel::HttpService because a singleton instance already exists");
	Pixel:HttpService::instance = this;

	curl_global_init(CURL_GLOBAL_ALL);
}

Pixel::HttpService::~HttpService()
{
	Pixel:HttpService::instance = nullptr;

	curl_global_cleanup();
}

Pixel::HttpService* Pixel::HttpService::instance = nullptr;
Pixel::HttpService* Pixel::HttpService::Singleton()
{
	assert(Pixel::HttpService::instance != nullptr);
	if (Pixel::HttpService::instance == nullptr)
		throw Pixel::Exception::FatalError("Failed to get Pixel::HttpService singleton because instance does not exist");
	return Pixel::HttpService::instance;
}

Pixel::URL Pixel::HttpService::GetInformationFromURL(std::string url)
{
	Pixel::URL urlInfo;
	size_t httpPos = url.find("http://");
	size_t httpsPos = url.find("https://");
	size_t domainPos;
	size_t pathPos;
	size_t paramPos;

	//Search for protocol
	if (httpsPos != std::string::npos)
	{
		//Using https
		urlInfo.protocol = "https";
		domainPos = httpsPos + 8;
	}
	else if (httpPos != std::string::npos)
	{
		//Using http
		urlInfo.protocol = "http";
		domainPos = httpPos + 7;
	}
	else
	{
		//Protocol not found, url is not formatted correctly
		urlInfo.isValid = false;
		return urlInfo;
	}

	urlInfo.isValid = true;

	//Search for path position (should be first / after protocol if there is a path)
	pathPos = url.find("/", domainPos);
	if (pathPos != std::string::npos)
	{
		urlInfo.domain = url.substr(domainPos, pathPos - domainPos);
	}
	else
	{
		//Assume no path
		urlInfo.domain = url.substr(domainPos, url.length() - domainPos);
		urlInfo.path = "/";
		return urlInfo;
	}

	//Search for url parameters (if any)
	paramPos = url.find("?", domainPos);
	if (paramPos != std::string::npos)
	{
		if ((paramPos + 1) <= url.length())
		{
			urlInfo.parameters = url.substr(paramPos, url.length() - paramPos);
		}
		urlInfo.path = url.substr(pathPos, paramPos - pathPos);
	}
	else
	{
		urlInfo.path = url.substr(pathPos, url.length() - pathPos);
		urlInfo.parameters = "?";
	}

	return urlInfo;
}

Pixel::HttpResponse Pixel::HttpService::Get(std::string url)
{
	CURL *curl;
	CURLcode code = CURLE_FAILED_INIT;
	std::ostringstream dataStream;
	std::ostringstream headersStream;

	Pixel::HttpResponse response;
	response.body = "";
	response.statusCode = 0U;
	response.success = false;

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

#ifndef NDEBUG
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Pixel::HttpService::_curlDataWriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataStream);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headersStream);

		code = curl_easy_perform(curl);

		if (code == CURLE_OK)
		{
			response.success = true;
			response.body = dataStream.str();
			response.rawHeaders = headersStream.str();

			//Parse raw headers into a std::map of the individual headers
			size_t lastLineStart = 0;
			for (size_t i = 0; i <= response.rawHeaders.length(); i++)
			{
				if (response.rawHeaders[i] == '\r' && response.rawHeaders[i + 1] == '\n')
				{
					std::string headerLine = response.rawHeaders.substr(lastLineStart, i - lastLineStart);
					if (lastLineStart == 0)
					{
						//This is the first header (the status code one)
						//Extract status code
						size_t statusCodeStart = headerLine.find(" ");
						if (statusCodeStart != std::string::npos)
						{
							size_t statusCodeEnd = headerLine.find(" ", statusCodeStart + 1);
							response.statusCode = (unsigned short)std::stoi(headerLine.substr(statusCodeStart + 1, statusCodeEnd - statusCodeStart + 1));
						}
					}
					else
					{
						//Normal header entry
						size_t kvpSplit = headerLine.find(":");
						if (kvpSplit != std::string::npos)
						{
							std::string key = headerLine.substr(0, kvpSplit);
							std::string value = headerLine.substr(kvpSplit + 2, headerLine.length() - (kvpSplit + 2));
							response.headers[key] = value;
						}
					}
					lastLineStart = i + 2;
				}
			}
		}
		else
		{
			throw Pixel::Exception::RuntimeError(std::string("curl_easy_perform() failed: ") + std::string(curl_easy_strerror(code)));
		}

		curl_easy_cleanup(curl);
	}

	return response;
}

Pixel::HttpResponse Pixel::HttpService::Post(std::string url, std::string &data)
{
	CURL *curl;
	CURLcode code = CURLE_FAILED_INIT;
	std::ostringstream dataStream;
	std::ostringstream headersStream;

	Pixel::HttpResponse response;
	response.body = "";
	response.statusCode = 0U;
	response.success = false;

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

#ifndef NDEBUG
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Pixel::HttpService::_curlDataWriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataStream);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headersStream);

		code = curl_easy_perform(curl);

		if (code == CURLE_OK)
		{
			response.success = true;
			response.body = dataStream.str();
			response.rawHeaders = headersStream.str();

			//Parse raw headers into a std::map of the individual headers
			size_t lastLineStart = 0;
			for (size_t i = 0; i <= response.rawHeaders.length(); i++)
			{
				if (response.rawHeaders[i] == '\r' && response.rawHeaders[i + 1] == '\n')
				{
					std::string headerLine = response.rawHeaders.substr(lastLineStart, i - lastLineStart);
					if (lastLineStart == 0)
					{
						//This is the first header (the status code one)
						//Extract status code
						size_t statusCodeStart = headerLine.find(" ");
						if (statusCodeStart != std::string::npos)
						{
							size_t statusCodeEnd = headerLine.find(" ", statusCodeStart + 1);
							response.statusCode = (unsigned short)std::stoi(headerLine.substr(statusCodeStart + 1, statusCodeEnd - statusCodeStart + 1));
						}
					}
					else
					{
						//Normal header entry
						size_t kvpSplit = headerLine.find(":");
						if (kvpSplit != std::string::npos)
						{
							std::string key = headerLine.substr(0, kvpSplit);
							std::string value = headerLine.substr(kvpSplit + 2, headerLine.length() - (kvpSplit + 2));
							response.headers[key] = value;
						}
					}
					lastLineStart = i + 2;
				}
			}
		}
		else
		{
			throw Pixel::Exception::RuntimeError(std::string("curl_easy_perform() failed: ") + std::string(curl_easy_strerror(code)));
		}

		curl_easy_cleanup(curl);
	}

	return response;
}

size_t Pixel::HttpService::_curlDataWriteCallback(char* buf, size_t size, size_t nmemb, void* userp)
{
	if (userp)
	{
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if (os.write(static_cast<char*>(buf), len))
		{
			return size * nmemb;
		}
	}
	return 0;
}