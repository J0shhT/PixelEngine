/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Include/Core/SoundService.h
*/

#pragma once

#include "Include/Common.h"

#include <fmod/fmod.hpp>

#undef PlaySound

#pragma warning(push)
#pragma warning(disable: 4251)

namespace Pixel {

	/**
	*  The Pixel::Sound struct is used to represent a playable sound.
	*  See Pixel::ContentProvider::LoadSoundFile() documentation for more details.
	*/
	struct PIXEL_API Sound
	{
		Sound(std::string filePath):
			filePath(filePath),
			volume(1.0f) { }

		std::string filePath; //* The path to the sound file to play, loaded by ContentProvider.
		float volume; //* The volume of the sound, 1.0f by default.
	};

	/**
	*  The Pixel::SoundService is a singleton service used to play sounds in the game.
	*  Supported sound file formats:
	- AIFF, ASF, ASX, DLS, FLAC, FSB, IT, M3U, MIDI, MOD, MP2, MP3, Ogg Vorbis,
	PLS, S3M, VAG, WAV, WAX, WMA, XM
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
			*  Updates the FMOD sound system.
			*/
			void Update();

			/**
			*  Plays the sound specified by the Pixel::Sound struct.
			*  This function automatically loads the sound file using
			the Pixel::ContentProvider service.
			*  See Pixel::Sound struct.
			*/
			void PlaySound(Pixel::Sound);

			/**
			*  Returns a pointer to the FMOD System struct.
			*  This function is mostly only for internal-usage.
			*/
			FMOD::System* GetSoundSystem() const;

		private:

			FMOD::System* _fmod;

	};

}

#pragma warning(pop)