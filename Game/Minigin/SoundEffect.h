#pragma once
#include "SDL_mixer.h"
#include <string>
class SoundEffect
{
public:
	~SoundEffect() = default;
	SoundEffect() = default;

	void Load(const std::string& path)
	{
		std::string clipName = "../Data/Sound/";
		clipName.append(path);
		
		const char* path_c = clipName.c_str();
		Mix_LoadWAV(path_c);
	};
	void SetVolume(const float volume)
	{
		m_Sound->volume = (Uint8)volume;
	}
	void Play()
	{
		m_Channel = Mix_PlayChannel(-1, m_Sound, 0);
	};
	bool IsPlaying()
	{
		return Mix_Playing(m_Channel);
	}
	bool IsLoaded()
	{
		return m_Sound != NULL;
	}
	void ReleaseSound()
	{
		Mix_FreeChunk(m_Sound);
	}
private:
	Mix_Chunk* m_Sound;
	int m_Channel;
};