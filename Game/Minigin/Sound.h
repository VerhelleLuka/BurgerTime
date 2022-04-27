#pragma once
#include "SDL_mixer.h"
using sound_id = unsigned short;

class sound_system
{
public:
	virtual ~sound_system() = default;
	virtual void play(const sound_id id, const float volume) = 0;
};

class sdl_sound_system : public sound_system
{
public:
	void play(const sound_id /*id*/, const float /*volume*/) override
	{
		Mix_Chunk* _sample;
		_sample = Mix_LoadWAV("../Data/Sound/Bomb_Explode.wav");
		Mix_PlayChannel(-1, _sample, 0);
	}
};

class ServiceLocator final
{

};