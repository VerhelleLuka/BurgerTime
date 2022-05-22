#pragma once
#include "Minigin.h"
#include "BurgerTimeStructs.h"
namespace dae
{
	class Scene;
	class BurgerTime
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		void CreatePeterPepperAndHUD(Transform spawnPos, Scene& scene, int playerNr) const;
		Transform ParseLevel(Scene& scene)const;
		void MakeLaddersAndPlatforms(Scene& scene, const std::vector<Ladder>& ladders, const std::vector<Platform>& platforms)const;
		void MakeBurgers(Scene& scene, const std::vector<Burger>& burgers) const;
		
		Minigin m_Minigin;
	};
}