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
	Pixel::ContentId contentId = Pixel::ContentProvider::Singleton()->LoadSoundFile(sound.filePath);
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

FMOD::System* Pixel::SoundService::GetSoundSystem() const
{
	return _fmod;
}
