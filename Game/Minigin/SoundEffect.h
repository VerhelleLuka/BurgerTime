#pragma once
#include "SDL_mixer.h"
#include <string>
class SoundEffect
{
public:
	~SoundEffect() = default;
	SoundEffect(const std::string& path)
	{
		const char* path_c = path.c_str();
		m_Sound = Mix_LoadWAV(path_c);
	}
	//void Load(const std::string& path)
	//{
	//	const char* path_c = path.c_str();
	//	Mix_LoadWAV(path_c); 
	//};
	void SetVolume(const float volume)
	{
		m_Sound->volume = (Uint8)volume;
	}
	void Play()
	{
		Mix_PlayChannel(-1, m_Sound, 0);
	};
	void ReleaseSound()
	{
		Mix_FreeChunk(m_Sound);
	}
private:
	Mix_Chunk* m_Sound;
};