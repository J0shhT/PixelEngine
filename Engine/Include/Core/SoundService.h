#pragma once

#include "Include/Common.h"

#include <fmod/fmod.hpp>

#undef PlaySound

namespace Pixel {

	struct PIXEL_API Sound
	{
		Sound(std::string filePath):
			filePath(filePath),
			volume(1.0f) { }

		std::string filePath;
		float volume;
	};

	/**
	*  TODO
	*/
	class PIXEL_API SoundService final
	{

		PIXEL_DEFINE_SINGLETON(Pixel::SoundService);

		public:

			/**
			*  Class constructor
			*/
			SoundService();

			/**
			*  Class deconstructor
			*/
			~SoundService();

			/**
			*  TODO
			*/
			void Update();

			/**
			*  TODO
			*/
			void PlaySound(Pixel::Sound);

			/**
			*  TODO
			*/
			FMOD::System* GetSoundSystem() const;

		private:

			FMOD::System* _fmod;

	};

}