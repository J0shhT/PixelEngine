/*
	Pixel Engine
	https://github.com/J0shhT/PixelEngine/

	Developed by Josh Theriault, 2018
	Licensed under GNU General Public License v3.0

	/Source/Core/SoundService.cpp
*/

#include "Include/Core/SoundService.h"

#include "Include/PixelError.h"

#include "Include/Core/ContentProvider.h"

PIXEL_DECLARE_SINGLETON(Pixel::SoundService);

Pixel::SoundService::SoundService()
{
	PIXEL_SINGLETON_CONSTRUCTOR(Pixel::SoundService);
	FMOD::System_Create(&_fmod);
	_fmod->init(32, FMOD_INIT_NORMAL, NULL);
}

Pixel::SoundService::~SoundService()
{
	_fmod->release();
	PIXEL_SINGLETON_DECONSTRUCTOR(Pixel::SoundService);
}

void Pixel::SoundService::Update()
{
	_fmod->update();
}

void Pixel::SoundService::PlaySound(Pixel::Sound sound)
{
	Pixel::ContentId contentId;
	if (sound.path.substr(0, 4) == "http")
	{
		//Sound is being loaded from online URL
		contentId = Pixel::ContentProvider::Singleton()->LoadSoundWeb(sound.path);
	}
	else
	{
		//Sound is being loaded from a local file
		contentId = Pixel::ContentProvider::Singleton()->LoadSoundFile(sound.path);
	}
	if (contentId != "")
	{
		auto soundContent = const_cast<Pixel::Content*>(Pixel::ContentProvider::Singleton()->Get(contentId));
		if (soundContent->type == Pixel::ContentType::Sound)
		{
			_fmod->playSound(soundContent->fmodSound, 0, false, &soundContent->fmodChannel);
			soundContent->fmodChannel->setVolume(sound.volume);
		}
	}
}

unsigned int Pixel::SoundService::GetTotalPlayingSounds() const
{
	unsigned int total = 0;
	auto sounds = Pixel::ContentProvider::Singleton()->GetOfType(Pixel::ContentType::Sound);
	for (auto iter = sounds.cbegin(); iter != sounds.cend(); iter++)
	{
		bool isPlaying = false;
		(*iter)->fmodChannel->isPlaying(&isPlaying);
		if (isPlaying)
		{
			total++;
		}
	}
	return total;
}

FMOD::System* Pixel::SoundService::GetSoundSystem() const
{
	return _fmod;
}

