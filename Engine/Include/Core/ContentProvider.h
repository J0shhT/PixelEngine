/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/ContentProvider.h
*/

#pragma once

#include "Include/Common.h"

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <fmod/fmod.hpp>

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  A unique id representing a piece of content in the ContentProvider.
	*/
	typedef std::string ContentId;

	/**
	*  The Pixel::ContentType enum is used to specify what type
	of content a Pixel::Content struct is representing.
	*/
	enum class ContentType
	{
		Null, //* Content that is not associated with anything, such as if an error occurs.
		Text, //* Content that represents a basic file in text form.
		Texture, //* Content that represents a texture to be rendered by the engine (png, jpg, etc).
		Sound //* Content that represents a sound file to be played by the engine (mp3, wav, etc).
	};

	/**
	*  The Pixel::Content struct is used to represent a piece of
	content loaded by the ContentProvider service.
	*/
	struct Content
	{
		Pixel::ContentType type = Pixel::ContentType::Null; //* The type of content this struct is representing.
		Pixel::ContentId id; //* The unique ID representing this piece of content in the ContentProvider.
		std::string filePath; //* The file path associated with this piece of content.
		std::string url; //* The online url associated with this piece of content.

		/**
		*  The full file contents of this piece of content.
		*  This property is only available for:
		ContentType::Text
		*/
		std::string fileContents;

		/**
		*  The width for this piece of content.
		*  This property is only available for:
		ContentType::Texture
		*/
		int width;

		/**
		*  The height for this piece of content.
		*  This property is only available for:
		ContentType::Texture
		*/
		int height;

		/**
		*  The internal OpenGL texture ID for this content.
		*  This property is only available for:
		ContentType::Texture
		*/
		GLuint glTextureId;

		/**
		*  The internal FMOD sound class (pointer) for this content.
		*  This property is only available for:
		ContentType::Sound
		*/
		FMOD::Sound* fmodSound = nullptr;

		/**
		*  The internal FMOD channel (pointer) for this content.
		*  This property is only available for:
		ContentType::Sound
		*/
		FMOD::Channel* fmodChannel = nullptr;
	};

	/**
	*  The Pixel::ContentProvider is a singleton service used to load, manage,
	and cache content into the engine to be used (such as textures, sounds, etc).

	*  Content is loaded via the various loading methods of ContentProvider such
	as ContentProvider::LoadTextureFile() or ContentProvider::LoadTextFile()

	*  All loading methods will return a Pixel::ContentId, which is a unique
	id that represents a peice of content managed by the ContentProvider.

	*  To fetch the loaded content, you must use ContentProvider::Get(contentId).

	*  When fetching (and loading) content, the ContentProvider automatically checks
	if you already previously loaded the content (cache system). If the content is
	already loaded, it will not load it again and instead just fetch the already
	loaded content.

	*  You can choose to manually unload content with ContentProvider::FreeContent()
	*/
	class PIXEL_API ContentProvider final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::ContentProvider);

		public:

			/**
			*  Class constructor
			*/
			ContentProvider();

			/**
			*  Class deconstructor
			*/
			~ContentProvider();

			/**
			*  Returns true if the specified ContentId is binded to an existing
			piece of content managed by the ContentProvider.
			*/
			bool DoesContentExist(Pixel::ContentId);

			/**
			*  Returns true if the content is already been loaded by the ContentProvider
			using the specified identifier.
			*  The identifier parameter is whatever you used to originally load
			the content, which is usually the file path.
			*/
			bool IsContentCached(std::string identifier);

			/**
			*  Returns an std::map containing stats for how many of each ContentType
			is currently loaded by ContentProvider.
			*  The key of the std::map is the type of content.
			*  The value of the std::map is the total number of content loaded.
			*/
			std::map<Pixel::ContentType, unsigned int> GetStats() const;

			/**
			*  Unloads the content binded to the specified ContentId.
			*/
			void FreeContent(Pixel::ContentId);

			/**
			*  Returns the piece of content binded to the specified ContentId.
			*  If an error occurs, a Pixel::Content struct with a Null ContentType
			will be returned (like if the content doesn't exist).
			*/
			const Pixel::Content* const Get(Pixel::ContentId);

			/**
			*  Returns a std::vector of all the loaded content of the specified ContentType.
			*/
			std::vector<Pixel::Content*> GetOfType(Pixel::ContentType);

			/**
			*  Loads a file as a basic text file from the specified file path.
			*/
			Pixel::ContentId LoadTextFile(std::string filePath);

			/**
			*  Loads a file as a basic text file from the specified online URL.
			*  If you set noCache to true, ContentProvider will bypass the cache system and
			will load the file again from the URL.
			*  If you have a URL that can return different file contents on each request,
			you will want to add a dummy parameter to the URL (example: http://example.com/?DUMMY)
			where DUMMY could be a randomly generated string.
			*/
			Pixel::ContentId LoadTextWeb(std::string url, bool noCache = false);

			/**
			*  Loads an image as a renderable OpenGL texture from the specified file path.
			*  Supported image file formats:
			- BMP (non-1bpp, non-RLE)
			- PNG (non-interlaced)
			- JPG (JPEG baseline)
			- TGA (greyscale, RGB, RGBA or indexed, uncompressed or RLE)
			- DDS (DXT1/2/3/4/5, uncompressed, cubemaps, can't read 3D DDS files)
			- HDR (converted to LDR)
			- PSD
			*/
			Pixel::ContentId LoadTextureFile(std::string filePath);

			/**
			*  Loads an image as a renderable OpenGL texture from the specified online URL.
			*  If you set noCache to true, ContentProvider will bypass the cache system and
			will load the image again from the URL.
			*  If you have a URL that can return different images on each request, you will
			want to add a dummy parameter to the URL (example: http://example.com/?DUMMY)
			where DUMMY could be a randomly generated string.
			*  Supported image file formats:
			- BMP (non-1bpp, non-RLE)
			- PNG (non-interlaced)
			- JPG (JPEG baseline)
			- TGA (greyscale, RGB, RGBA or indexed, uncompressed or RLE)
			- DDS (DXT1/2/3/4/5, uncompressed, cubemaps, can't read 3D DDS files)
			- HDR (converted to LDR)
			- PSD
			*/
			Pixel::ContentId LoadTextureWeb(std::string url, bool noCache = false);

			/**
			*  Loads a sound file as a playable FMOD sound from the specified file path.
			*  Supported sound file formats:
			- AIFF, ASF, ASX, DLS, FLAC, FSB, IT, M3U, MIDI, MOD, MP2, MP3, Ogg Vorbis, 
			PLS, S3M, VAG, WAV, WAX, WMA, XM
			*/
			Pixel::ContentId LoadSoundFile(std::string filePath);

			/**
			*  Loads a sound file as a playable FMOD sound from the specified online URL.
			*  If you set noCache to true, ContentProvider will bypass the cache system and
			will load the sound again from the URL.
			*  If you have a URL that can return different sounds on each request, you will
			want to add a dummy parameter to the URL (example: http://example.com/?DUMMY)
			where DUMMY could be a randomly generated string.
			*  Supported sound file formats:
			- AIFF, ASF, ASX, DLS, FLAC, FSB, IT, M3U, MIDI, MOD, MP2, MP3, Ogg Vorbis,
			PLS, S3M, VAG, WAV, WAX, WMA, XM
			*/
			Pixel::ContentId LoadSoundWeb(std::string url, bool noCache = false);

		private:

			std::map<Pixel::ContentId, Pixel::Content*> _loadedContent;
			std::map<std::string, Pixel::ContentId> _loadedContentCache;
			Pixel::Content* _nullContent;

	};

}

#pragma warning(pop)