#pragma once
using sound_id = unsigned short;

namespace dae
{

	class sound_system
	{
	private:
		class sound_systemImpl;
		sound_systemImpl* m_pImpl;
	public:
		sound_system();
		~sound_system();
		virtual void Play(const sound_id id, const float volume);

		virtual void RegisterSound(const sound_id id, const std::string& path);
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

		void RegisterSound(const sound_id id, const std::string& path) override;
		void Play(const sound_id id, const float volume) override;
	};
	class ServiceLocator final
	{
	private:
		static sound_system* m_ssInstance;
		static null_sound_system m_ssDefault;

	public:
		static sound_system& GetSoundSystem() { return *m_ssInstance; }
		static void RegisterSoundSystem(sound_system* ss);


	};

}
