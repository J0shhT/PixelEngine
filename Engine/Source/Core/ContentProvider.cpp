#include "Include/Core/ContentProvider.h"

#include "Include/PixelError.h"
#include "Include/Core/PixelApp.h"

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

void Pixel::ContentProvider::FreeContent(Pixel::ContentId id)
{
	//Check if content exists
	if (DoesContentExist(id))
	{
		const Pixel::Content* const content = Get(id);
		std::string identifier;

		if (content->type == Pixel::ContentType::Texture)
		{
			//Cleanup texture
			identifier = content->filePath;
			glDeleteTextures(1, &content->glTextureId);
		}
		else if (content->type == ContentType::Sound)
		{
			//Cleanup fmod sound
			identifier = content->filePath;
			content->fmodSound->release();
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

Pixel::ContentId Pixel::ContentProvider::LoadTextFile(std::string filePath)
{
	std::string filePathRaw = filePath;
#ifdef _DEBUG
	filePath = "J:/PixelEngine/Dev/Release/" + filePath;
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

Pixel::ContentId Pixel::ContentProvider::LoadTextureFile(std::string filePath)
{
	std::string filePathRaw = filePath;
#ifdef _DEBUG
	filePath = "J:/PixelEngine/Dev/Release/" + filePath;
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
