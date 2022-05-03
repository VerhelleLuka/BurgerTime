#include "MiniginPCH.h"
#include "Sound.h"
#include "SDL_mixer.h"
#include <queue>
#include <thread>
#include <condition_variable>

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
	sound_systemImpl()
	{
		m_thread = std::thread(&sound_systemImpl::Thread, this);
		m_IsRunning = true;
	};
	~sound_systemImpl()
	{
		m_IsRunning = false;
		m_Cv.notify_one();
		m_thread.join();
	};
	void RegisterSound(const sound_id id, const std::string& path)
	{
		audioClips[id] = path.c_str();
	}

	void Play(const sound_id id, const float volume)
	{
		m_SoundsToPlay.push(id);
		m_Cv.notify_one();
	}


private:
	std::thread m_thread;
	std::condition_variable m_Cv;
	std::queue<unsigned short> m_SoundsToPlay;
	std::mutex m_Mutex;
	bool m_IsRunning;
	void Thread(const sound_id id, const float volume)
	{
		std::unique_lock lock(m_Mutex);

		while (m_IsRunning)
		{
			m_Cv.wait(lock);
			while (!m_SoundsToPlay.empty())
			{
				Mix_Chunk* _sample;
				const char* audioClip = audioClips[m_SoundsToPlay.front()];
				std::string clipName = "../Data/Sound/";
				clipName.append(audioClip);
				const char* clipNameChar = clipName.c_str();

				lock.unlock();
				_sample = Mix_LoadWAV(clipNameChar);
				_sample->volume = (Uint8)volume;

				Mix_PlayChannel(-1, _sample, 0);

				lock.lock();
				m_SoundsToPlay.pop();
			}
		}

	}
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