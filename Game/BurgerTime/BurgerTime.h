#pragma once
#include "Minigin.h"
#include "BurgerTimeStructs.h"
#include "GameManager.h"
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
		void LoadLevel1(GameMode gameMode) const;
		void LoadLevel2(GameMode gameMode) const;
		void LoadLevel3(GameMode gameMode) const;
	private:
		void CreatePeterPepperAndHUD(Transform spawnPos, Scene& scene, int playerNr, bool andHUD) const;
		GameObject* CreateEnemyTemplate(Scene& scene, int sceneNr, Float2 position) const;
		void CreateMenu(Scene& scene) const;
		void CreateTray(Scene& scene, int sceneNr, Float2 position) const;
		void CreateMenuButton(Scene& scene, Float2 position, GameMode gameMode,const std::string& text) const;
		Transform ParseLevel(Scene& scene, int sceneNr, const std::string& levelName)const;
		void MakeLaddersAndPlatforms(Scene& scene, const std::vector<Ladder>& ladders, const std::vector<Platform>& platforms, int sceneNr)const;
		void MakeBurgers(Scene& scene, const std::vector<Burger>& burgers, int sceneNr) const;
		void MakeEnemySpawner(std::vector<Float2> spawnPositions) const;


		Minigin m_Minigin;

		GameObject* m_pEnemyTemplate;
	};
}