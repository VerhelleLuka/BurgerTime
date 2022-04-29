#pragma once
#include "SDL_mixer.h"
using sound_id = unsigned short;

//enum sounds
//{
//	Explosion = 1,
//	Hurt = 2
//};

const char* audioClips[] =
{
"Bomb_Explode.wav",
"Hurt.wav",
};
class sound_system
{
public:
	virtual ~sound_system() = default;
	virtual void Play(const sound_id id, const float volume) = 0;

	virtual void RegisterSound(const sound_id id, const std::string& path)
	{
		audioClips[id] = path.c_str();
	}
};


class sdl_sound_system : public sound_system
{
public:
	void Play(const sound_id id, const float volume) override
	{
		Mix_Chunk* _sample;
		const char* audioClip = audioClips[id];
		std::string clipName = "../Data/Sound/";
		clipName.append(audioClip);
		const char* clipNameChar = clipName.c_str();

		_sample = Mix_LoadWAV(clipNameChar);
		_sample->volume = (Uint8)volume;

		Mix_PlayChannel(-1, _sample, 0);
	}
};

class null_sound_system final : public sound_system
{
	void Play(const sound_id /*id*/, const float /*volume*/) override {};
};

class logging_sound_system final : public sound_system
{
	sound_system* m_ssReal;

public:
	logging_sound_system(sound_system* ss) : m_ssReal(ss) {}
	~logging_sound_system() { delete m_ssReal; }

	void RegisterSound(const sound_id id, const std::string& path) override {
		m_ssReal->RegisterSound(id, path);
	}
	void Play(const sound_id id, const float volume) override
	{
		m_ssReal->Play(id, volume);
		std::cout << "Playing " << id << " at volume " << volume << std::endl;
	}
};
class ServiceLocator final
{
private:
	static sound_system* m_ssInstance;
	static null_sound_system m_ssDefault;

public:
	static sound_system& GetSoundSystem() { return *m_ssInstance; }
	static void RegisterSoundSystem(sound_system* ss)
	{
		m_ssInstance = ss == nullptr ? &m_ssDefault : ss;
	}

};
null_sound_system ServiceLocator::m_ssDefault;
sound_system* ServiceLocator::m_ssInstance = &m_ssDefault;