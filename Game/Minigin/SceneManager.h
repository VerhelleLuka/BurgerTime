#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		void Initialize();
		void SetActiveScene(Scene* scene);
		void SetActiveSceneByName(const std::string& name);
		const std::string& GetActiveSceneName() const;
		Scene& GetActiveScene()const;
		int GetActiveSceneNr() const;

		bool GetSceneChanged() const { return m_SceneChanged; }
		void SetSceneChanged(bool sceneChanged) { m_SceneChanged = sceneChanged; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() : m_pActiveScene(nullptr) {};
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		Scene* m_pActiveScene = nullptr;
		bool m_SceneChanged = false;
	};
}
