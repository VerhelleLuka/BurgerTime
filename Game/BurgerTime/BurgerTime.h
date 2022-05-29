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
		void CreatePeterPepperAndHUD(Transform spawnPos, Scene& scene, int playerNr, bool andHUD, int sceneNr) const;
		void CreateEnemy(Scene& scene, int sceneNr) const;
		void CreateMenu(Scene& scene) const;
		Transform ParseLevel(Scene& scene, int sceneNr)const;
		void MakeLaddersAndPlatforms(Scene& scene, const std::vector<Ladder>& ladders, const std::vector<Platform>& platforms, int sceneNr)const;
		void MakeBurgers(Scene& scene, const std::vector<Burger>& burgers, int sceneNr) const;
		void MakeCommands(int playerNr, GameObject* go, bool andHUD) const;
		void AddRigidBodyToPhysics(int sceneNr, std::shared_ptr<RigidBodyComponent> rB) const;
		Minigin m_Minigin;
	};
}