#pragma once
struct SDL_Window;
namespace dae
{
	class Scene;
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		void CreatePeterPepperAndHUD(Scene& scene,int playerNr ) const;
		void ParseLevel(Scene& scene)const;
		bool m_SteamApi;

	};
}