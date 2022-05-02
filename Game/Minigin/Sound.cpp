#include "MiniginPCH.h"
#include "Sound.h"
#include "SDL_mixer.h"
#include <queue>
#include <thread>

const char* audioClips[] =
{
"Bomb_Explode.wav",
"Hurt.wav",
};
dae::null_sound_system dae::ServiceLocator::m_ssDefault;
dae::sound_system* dae::ServiceLocator::m_ssInstance = &m_ssDefault;

class dae::sound_system::sound_systemImpl
{

public:
	sound_systemImpl() {};
	~sound_systemImpl() = default;
	void RegisterSound(const sound_id id, const std::string& path)
	{
		audioClips[id] = path.c_str();
	}

	void Play(const sound_id id, const float volume)
	{
		m_SoundsToPlay.push(id);
		while (!m_SoundsToPlay.empty())
		{
			Mix_Chunk* _sample;
			const char* audioClip = audioClips[m_SoundsToPlay.front()];
			std::string clipName = "../Data/Sound/";
			clipName.append(audioClip);
			const char* clipNameChar = clipName.c_str();

			_sample = Mix_LoadWAV(clipNameChar);
			_sample->volume = (Uint8)volume;

			Mix_PlayChannel(-1, _sample, 0);
			m_SoundsToPlay.pop();
		}

	}
private:
	std::thread m_thread;

	std::queue<unsigned short> m_SoundsToPlay;
};

dae::sound_system::sound_system()
	:m_pImpl(new sound_systemImpl())
{

}
dae::sound_system::~sound_system()
{
	delete m_pImpl;
}


void dae::sound_system::RegisterSound(const sound_id id, const std::string& path)
{
	m_pImpl->RegisterSound(id, path);
}

void dae::sound_system::Play(const sound_id id, const float volume)
{
	m_pImpl->Play(id, volume);
}



void dae::logging_sound_system::Play(const sound_id id, const float volume)
{
	m_ssReal->Play(id, volume);
	std::cout << "Playing " << id << " at volume " << volume << std::endl;
}

void dae::logging_sound_system::RegisterSound(const sound_id id, const std::string& path)
{
	m_ssReal->RegisterSound(id, path);
}

void dae::ServiceLocator::RegisterSoundSystem(sound_system* ss)
{
	m_ssInstance = ss == nullptr ? &m_ssDefault : ss;
}