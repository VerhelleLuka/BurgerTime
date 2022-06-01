#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Physics.h"
void dae::SceneManager::Update(float deltaTime)
{
	if (m_pActiveScene)
		m_pActiveScene->Update(deltaTime);
	//for(auto& scene : m_Scenes)
	//{
	//	scene->Update(deltaTime);
	//}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	if (m_pActiveScene)
		m_pActiveScene->FixedUpdate(deltaTime);

}

void dae::SceneManager::Render()
{
	if (m_pActiveScene)
		m_pActiveScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	scene->SetIndex(int(m_Scenes.size() - 1));
	return *scene;
}

void dae::SceneManager::SetActiveScene(Scene* scene)
{
	m_SceneChanged = true;
	m_pActiveScene = scene;
}
void dae::SceneManager::SetActiveSceneByName(const std::string& name)
{
	for (std::shared_ptr<Scene>scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_SceneChanged = true;
			m_pActiveScene = scene.get();
			return;
		}
	}
}
const std::string& dae::SceneManager::GetActiveSceneName() const
{
	return m_pActiveScene->GetName();
}

dae::Scene& dae::SceneManager::GetActiveScene() const
{
	return *m_pActiveScene;
}

int dae::SceneManager::GetActiveSceneNr() const
{
	for (int i{}; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i].get() == m_pActiveScene)
		{
			return i;
		}
	}
	return 0;
}