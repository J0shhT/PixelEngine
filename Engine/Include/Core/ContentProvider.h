#pragma once

#include "Include/Common.h"

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <fmod/fmod.hpp>

namespace Pixel {

	typedef std::string ContentId;

	/**
	*  TODO
	*/
	enum class ContentType
	{
		Null,
		Text,
		Texture,
		Sound
	};

	/**
	*  TODO
	*/
	struct Content
	{
		Pixel::ContentType type = Pixel::ContentType::Null;
		Pixel::ContentId id;
		std::string filePath;
		std::string fileContents;
		int width;
		int height;
		GLuint glTextureId;
		FMOD::Sound* fmodSound = nullptr;
		FMOD::Channel* fmodChannel = nullptr;
	};

	/**
	*  TODO
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
			*  TODO
			*/
			bool DoesContentExist(Pixel::ContentId);

			/**
			*  TODO
			*/
			bool IsContentCached(std::string identifier);

			/**
			*  TODO
			*/
			void FreeContent(Pixel::ContentId);

			/**
			*  TODO
			*/
			const Pixel::Content* const Get(Pixel::ContentId);

			/**
			*  TODO
			*/
			Pixel::ContentId LoadTextFile(std::string filePath);

			/**
			*  TODO
			*/
			Pixel::ContentId LoadTextureFile(std::string filePath);

			/**
			*  TODO
			*/
			Pixel::ContentId LoadSoundFile(std::string filePath);

		private:

			std::map<Pixel::ContentId, Pixel::Content*> _loadedContent;
			std::map<std::string, Pixel::ContentId> _loadedContentCache;
			Pixel::Content* _nullContent;

	};

}