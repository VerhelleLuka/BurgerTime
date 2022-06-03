#pragma once
#include "Minigin.h"
#include "BurgerTimeStructs.h"
namespace dae
{
	class Scene;
	enum class EnemyType;
	class BurgerTime
	{
	public:
		void Initialize();
		void LoadGame();
		void Cleanup();
		void Run();
	private:
		void CreatePeterPepperAndHUD(Transform spawnPos, Scene& scene, int playerNr, bool andHUD, int sceneNr) const;
		GameObject* CreateEnemyTemplate(Scene& scene, int sceneNr, Float2 position) const;
		void CreateMenu(Scene& scene) const;
		void CreateTray(Scene& scene, int sceneNr, Float2 position) const;
		Transform ParseLevel(Scene& scene, int sceneNr)const;
		void MakeLaddersAndPlatforms(Scene& scene, const std::vector<Ladder>& ladders, const std::vector<Platform>& platforms, int sceneNr)const;
		void MakeBurgers(Scene& scene, const std::vector<Burger>& burgers, int sceneNr) const;
		void MakeCommands(int playerNr, GameObject* go, bool andHUD) const;
		void MakeEnemySpawner(std::vector<Float2> spawnPositions);
		Minigin m_Minigin;

		GameObject* m_pEnemyTemplate;
	};
}