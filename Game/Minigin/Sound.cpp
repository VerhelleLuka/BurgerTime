#include "MiniginPCH.h"
#include "Sound.h"
#include "SDL_mixer.h"
#include <queue>
#include <thread>
#include <condition_variable>
#include "SoundEffect.h"

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
		m_Thread = std::thread(&sound_systemImpl::Play, this);
		m_IsRunning = true;

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			exit(2);
		}
		if (Mix_AllocateChannels(16) < 0)
		{
			exit(-1);
		}
		std::string path = "../Data/Sound/Bomb_Explode.wav";
		m_Sounds.push_back(path);
		path = "../Data/Sound/Hurt.wav";
		m_Sounds.push_back(path);
	};
	~sound_systemImpl()
	{
		m_IsRunning = false;
		m_Cv.notify_one();
		for (int i{}; i < m_Sounds.size(); ++i)
		{
			m_Sounds[i].ReleaseSound();
		}
		Mix_CloseAudio();
		m_Thread.join();

	};
	void RegisterSound(const sound_id id, const std::string& path)
	{
		audioClips[id] = path.c_str();
		m_Sounds.push_back(path);
	}

	void AddSoundToQ(const sound_id id, const float volume)
	{
		if (audioClips[id] != NULL)
		{
			const char* audioClip = audioClips[id];
			std::string clipName = "../Data/Sound/";
			clipName.append(audioClip);
			m_Sounds[id].SetVolume(volume);

			m_SoundsToPlay.push(std::make_pair(id, volume));
			m_Cv.notify_one();
		}
		else
		{
			std::cout << "Invalid ID\n";
		}
	}


private:
	std::thread m_Thread;
	std::condition_variable m_Cv;
	std::vector<SoundEffect> m_Sounds;
	std::queue<std::pair<sound_id, float>> m_SoundsToPlay;
	std::mutex m_Mutex;
	bool m_IsRunning;
	void Play()
	{
		std::unique_lock lock(m_Mutex);

		while (m_IsRunning)
		{


			m_Cv.wait(lock);
			while (!m_SoundsToPlay.empty())
			{
				//Mix_Chunk* _sample;
				//const char* audioClip = audioClips[m_SoundsToPlay.front().first];
				//std::string clipName = "../Data/Sound/";
				//clipName.append(audioClip);
				//const char* clipNameChar = clipName.c_str();

				//lock.unlock();
				//_sample = Mix_LoadWAV(clipNameChar);
				//_sample->volume = (Uint8)m_SoundsToPlay.front().second;

				//Mix_PlayChannel(-1, _sample, 0);

				//lock.lock();
				//m_SoundsToPlay.pop();


				lock.unlock();
				m_Sounds[m_SoundsToPlay.front().first].Play();
				//m_SoundsToDelete.push(m_SoundsToPlay2.front());

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
	m_pImpl->AddSoundToQ(id, volume);
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