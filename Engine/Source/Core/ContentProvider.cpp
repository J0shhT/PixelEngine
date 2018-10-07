/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Core/ContentProvider.cpp
*/

#include "Include/Core/ContentProvider.h"

#include "Include/PixelError.h"

#include "Include/Core/SoundService.h"
#include "Include/Network/HttpService.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

PIXEL_DECLARE_SINGLETON(Pixel::ContentProvider);

Pixel::ContentProvider::ContentProvider()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::ContentProvider);
	
	//Null content singleton object
	Pixel::Content* nullContent = new Pixel::Content();
	nullContent->type = Pixel::ContentType::Null;
	_nullContent = nullContent;
}

Pixel::ContentProvider::~ContentProvider()
{
	delete _nullContent;
	if (_loadedContent.size() > 0)
	{
		for (auto iter = _loadedContent.begin();;)
		{
			FreeContent(iter->first);
			iter = _loadedContent.begin();
			if (_loadedContent.size() == 0)
			{
				break;
			}
		}
	}
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::ContentProvider);
}

bool Pixel::ContentProvider::DoesContentExist(Pixel::ContentId id)
{
	return _loadedContent.find(id) != _loadedContent.end();
}

bool Pixel::ContentProvider::IsContentCached(std::string identifier)
{
	return _loadedContentCache.find(identifier) != _loadedContentCache.end();
}

std::map<Pixel::ContentType, unsigned int> Pixel::ContentProvider::GetStats() const
{
	std::map<Pixel::ContentType, unsigned int> stats = {
		{ Pixel::ContentType::Null,			0 },
		{ Pixel::ContentType::Text,			0 },
		{ Pixel::ContentType::Texture,		0 },
		{ Pixel::ContentType::Sound,		0 },
	};

	for (auto iter = _loadedContent.cbegin(); iter != _loadedContent.cend(); iter++)
	{
		assert(stats.find(iter->second->type) != stats.end());
		stats[iter->second->type]++;
	}

	return stats;
}

void Pixel::ContentProvider::FreeContent(Pixel::ContentId id)
{
	//Check if content exists
	if (DoesContentExist(id))
	{
		const Pixel::Content* const content = Get(id);
		std::string identifier;

		if (content->type == ContentType::Text)
		{

		}
		else if (content->type == Pixel::ContentType::Texture)
		{
			//Cleanup texture
			identifier = content->filePath;
			glDeleteTextures(1, &content->glTextureId);
		}
		else if (content->type == ContentType::Sound)
		{
			
		}

		delete _loadedContent.at(id);
		_loadedContent.erase(id);

		if (IsContentCached(identifier))
		{
			_loadedContentCache.erase(identifier);
		}

		Pixel::StandardOut::Singleton()->Printf(Pixel::OutputType::Info, "ContentProvider unloaded content \"%s\"", id);
	}
	else
	{
		PixelError("ContentProvider failed to unload content of id \"" + id + "\" (does not exist)");
	}
}

const Pixel::Content* const Pixel::ContentProvider::Get(Pixel::ContentId id)
{
	if (id == "")
	{
		return const_cast<const Pixel::Content* const>(_nullContent);
	}

	if (DoesContentExist(id))
	{
		return const_cast<const Pixel::Content* const>(_loadedContent.at(id));
	}
	else
	{
		PixelError("ContentProvider::Get() - Failed to fetch content of id \"" + id + "\"  (does not exist)");
		return const_cast<const Pixel::Content* const>(_nullContent);
	}
}

std::vector<Pixel::Content*> Pixel::ContentProvider::GetOfType(Pixel::ContentType type)
{
	auto content = std::vector<Pixel::Content*>();

	for (auto iter = _loadedContent.cbegin(); iter != _loadedContent.cend(); iter++)
	{
		if (type == iter->second->type)
		{
			content.push_back(iter->second);
		}
	}

	return content;
}

Pixel::ContentId Pixel::ContentProvider::LoadTextFile(std::string filePath)
{
	std::string filePathRaw = filePath;
#ifdef _DEBUG
	filePath = DEBUG_BUILD_FILE_DIR + filePath;
#endif

	if (IsContentCached(filePathRaw))
	{
		return _loadedContentCache.at(filePathRaw);
	}
	else
	{
		Pixel::Content* content = new Pixel::Content();
		content->type = ContentType::Text;
		content->id = boost::lexical_cast<std::string>(boost::uuids::random_generator()());

		std::ifstream file(filePath);
		if (file.good())
		{
			std::stringstream fileBuffer;
			fileBuffer << file.rdbuf();
			content->fileContents = fileBuffer.str();
			content->filePath = filePathRaw;
		}
		else
		{
			PixelError("ContentProvider failed to load content \"" + filePathRaw + "\"");
			return std::string("");
		}

		_loadedContent.emplace(content->id, content);
		_loadedContentCache.emplace(content->filePath, content->id);

		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info,
			("ContentProvider loaded content \"" + content->filePath + "\" with id \"" + content->id + "\"").c_str()
		);

		return content->id;
	}

	return std::string("");
}

Pixel::ContentId Pixel::ContentProvider::LoadTextWeb(std::string url, bool noCache)
{
	if (IsContentCached(url))
	{
		return _loadedContentCache.at(url);
	}
	else
	{
		Pixel::Content* content = new Pixel::Content();
		content->type = ContentType::Text;
		if (IsContentCached(url))
		{
			content->id = _loadedContentCache.at(url);
		}
		else
		{
			content->id = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
		}

		Pixel::HttpResponse response = Pixel::HttpService::Singleton()->Get(url);
		if (response.success && response.statusCode == 200)
		{
			content->fileContents = response.body;
			content->url = url;
		}
		else
		{
			PixelError("ContentProvider failed to load content \"" + url + "\"");
			return std::string("");
		}

		if (IsContentCached(url))
		{
			_loadedContent[content->id] = content;
		}
		else
		{
			_loadedContent.emplace(content->id, content);
			_loadedContentCache.emplace(content->url, content->id);
		}

		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info,
			("ContentProvider loaded content \"" + content->url + "\" with id \"" + content->id + "\"").c_str()
		);

		return content->id;
	}

	return std::string("");
}

Pixel::ContentId Pixel::ContentProvider::LoadTextureFile(std::string filePath)
{
	std::string filePathRaw = filePath;
#ifdef _DEBUG
	filePath = DEBUG_BUILD_FILE_DIR + filePath;
#endif

	if (IsContentCached(filePathRaw))
	{
		return _loadedContentCache.at(filePathRaw);
	}
	else
	{
		Pixel::Content* content = new Pixel::Content();
		content->type = ContentType::Texture;
		content->id = boost::lexical_cast<std::string>(boost::uuids::random_generator()());

		unsigned char* image;
		if (image = SOIL_load_image(filePath.c_str(), &content->width, &content->height, 0, SOIL_LOAD_RGBA))
		{
			glGenTextures(1, &content->glTextureId);
			glBindTexture(GL_TEXTURE_2D, content->glTextureId);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				content->width,
				content->height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				image
			);
			SOIL_free_image_data(image);
			content->filePath = filePathRaw;
		}
		else
		{
			SOIL_free_image_data(image);
			PixelError("ContentProvider failed to load content \"" + filePathRaw + "\"");
			return std::string("");
		}

		_loadedContent.emplace(content->id, content);
		_loadedContentCache.emplace(content->filePath, content->id);

		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info,
			("ContentProvider loaded content \"" + content->filePath + "\" with id \"" + content->id + "\"").c_str()
		);

		return content->id;
	}

	return std::string("");
}

Pixel::ContentId Pixel::ContentProvider::LoadTextureWeb(std::string url, bool noCache)
{
	if (IsContentCached(url) && !noCache)
	{
		return _loadedContentCache.at(url);
	}
	else
	{
		Pixel::Content* content = new Pixel::Content();
		content->type = ContentType::Texture;
		if (IsContentCached(url))
		{
			content->id = _loadedContentCache.at(url);
		}
		else
		{
			content->id = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
		}

		Pixel::HttpResponse response = Pixel::HttpService::Singleton()->Get(url);
		if (response.success && response.statusCode == 200)
		{
			const char* data = response.body.c_str();
			size_t dataLength = response.body.size();

			unsigned char* image;
			if (image = SOIL_load_image_from_memory((const unsigned char*)data, dataLength, &content->width, &content->height, 0, SOIL_LOAD_RGBA))
			{
				glGenTextures(1, &content->glTextureId);
				glBindTexture(GL_TEXTURE_2D, content->glTextureId);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RGBA,
					content->width,
					content->height,
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					image
				);
				SOIL_free_image_data(image);
				content->url = url;
			}
			else
			{
				SOIL_free_image_data(image);
				PixelError("ContentProvider failed to load content \"" + url + "\"");
				return std::string("");
			}
		}
		else
		{
			PixelError("ContentProvider failed to load content \"" + url + "\"");
			return std::string("");
		}

		if (IsContentCached(url))
		{
			_loadedContent[content->id] = content;
		}
		else
		{
			_loadedContent.emplace(content->id, content);
			_loadedContentCache.emplace(content->url, content->id);
		}

		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info,
			("ContentProvider loaded content \"" + content->url + "\" with id \"" + content->id + "\"").c_str()
		);

		return content->id;
	}

	return std::string("");
}

Pixel::ContentId Pixel::ContentProvider::LoadSoundFile(std::string filePath)
{
	std::string filePathRaw = filePath;
#ifdef _DEBUG
	filePath = DEBUG_BUILD_FILE_DIR + filePath;
#endif

	if (IsContentCached(filePathRaw))
	{
		return _loadedContentCache.at(filePathRaw);
	}
	else
	{
		Pixel::Content* content = new Pixel::Content();
		content->type = ContentType::Sound;
		content->id = boost::lexical_cast<std::string>(boost::uuids::random_generator()());

		FMOD::System* fmod = Pixel::SoundService::Singleton()->GetSoundSystem();
		FMOD::Sound* sound;
		FMOD::Channel* channel = 0;
		FMOD_RESULT result = fmod->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &sound);
		if (result == FMOD_OK)
		{
			content->fmodSound = sound;
			content->fmodChannel = channel;
			content->filePath = filePathRaw;
		}
		else
		{
			PixelError("ContentProvider failed to load content \"" + filePathRaw + "\"");
			return std::string("");
		}

		_loadedContent.emplace(content->id, content);
		_loadedContentCache.emplace(content->filePath, content->id);

		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info,
			("ContentProvider loaded content \"" + content->filePath + "\" with id \"" + content->id + "\"").c_str()
		);

		return content->id;
	}

	return std::string("");
}

Pixel::ContentId Pixel::ContentProvider::LoadSoundWeb(std::string url, bool noCache)
{
	if (IsContentCached(url) && !noCache)
	{
		return _loadedContentCache.at(url);
	}
	else
	{
		Pixel::Content* content = new Pixel::Content();
		content->type = ContentType::Sound;
		if (IsContentCached(url))
		{
			content->id = _loadedContentCache.at(url);
		}
		else
		{
			content->id = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
		}

		Pixel::HttpResponse response = Pixel::HttpService::Singleton()->Get(url);
		if (response.success && response.statusCode == 200)
		{
			FMOD::System* fmod = Pixel::SoundService::Singleton()->GetSoundSystem();
			FMOD::Sound* sound;
			FMOD::Channel* channel = 0;

			FMOD_CREATESOUNDEXINFO soundInfo = { 0 };
			soundInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
			soundInfo.length = response.body.size();

			const char* data = response.body.c_str();
			FMOD_RESULT result = fmod->createSound(data, FMOD_DEFAULT | FMOD_OPENMEMORY, &soundInfo, &sound);
			if (result == FMOD_OK)
			{
				content->fmodSound = sound;
				content->fmodChannel = channel;
				content->url = url;
			}
			else
			{
				PixelError("ContentProvider failed to load content \"" + url + "\"");
				return std::string("");
			}
		}
		else
		{
			PixelError("ContentProvider failed to load content \"" + url + "\"");
			return std::string("");
		}

		if (IsContentCached(url))
		{
			_loadedContent[content->id] = content;
		}
		else
		{
			_loadedContent.emplace(content->id, content);
			_loadedContentCache.emplace(content->url, content->id);
		}

		Pixel::StandardOut::Singleton()->Print(Pixel::OutputType::Info,
			("ContentProvider loaded content \"" + content->url + "\" with id \"" + content->id + "\"").c_str()
		);

		return content->id;
	}

	return std::string("");
}
