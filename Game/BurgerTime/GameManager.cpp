#include "GameManager.h"
#include "BurgerTime.h"
#include "BurgerTimeStructs.h"
#include <string>
#include "SceneManager.h"
#include "Subject.cpp"
#include "Scene.h"
#include "PeterPepper.h"
#include "Enemy.h"
#include "BurgerComponent.h"
#include "InputManager.h"
dae::GameManager::GameManager()
	: m_pBurgerTime(nullptr),
	m_Points(0),
	m_NrBurgers(0),
	m_CompletedBurgers(0),
	m_CurrentLevelIndex(0),
	m_LevelComplete(false),
	m_Lives(3)
{
	m_LevelNames.push_back("MainMenu");
	for (int i{ 0 }; i < 3; ++i)
	{
		std::string levelName = "Level";
		levelName.append(std::to_string(i + 1));
		m_LevelNames.push_back(levelName);
	}
}
void dae::GameManager::SetBurgerTimeGame(BurgerTime* burgerTime)
{
	m_pBurgerTime = burgerTime;
}

void dae::GameManager::BurgerCompleted()
{
	m_CompletedBurgers++;
	std::cout << m_CompletedBurgers << " " << m_NrBurgers << "\n";
	if (m_CompletedBurgers >= m_NrBurgers && !m_LevelComplete && SceneManager::GetInstance().GetActiveScene().GetName() != "MainMenu")
	{
		m_CompletedBurgers = 0;
		++m_CurrentLevelIndex;
		m_LevelComplete = true;
		std::shared_ptr<EventArgs> emptyArgs = std::make_shared<EventArgs>();
		Notify(EventType::WIN, emptyArgs);
		ClearObservers();
	}

}
//
void dae::GameManager::LoadLevel(const std::string& levelName)
{
	SceneManager::GetInstance().GetActiveScene().MarkForDestroy();
	if (levelName == "MainMenu")
	{
		m_pBurgerTime->LoadLevel1(m_GameMode, "MainMenu");
	}
	else if (levelName == "Same")
	{
		m_pBurgerTime->LoadLevel1(m_GameMode, SceneManager::GetInstance().GetActiveSceneName());
	}
	else if (SceneManager::GetInstance().GetActiveSceneName() == "MainMenu")
	{
		m_pBurgerTime->LoadLevel1(m_GameMode, "Level1");
	}
	else if (SceneManager::GetInstance().GetActiveSceneName() == "Level1")
	{
		m_pBurgerTime->LoadLevel1(m_GameMode, "Level2");
	}
	else if (SceneManager::GetInstance().GetActiveSceneName() == "Level2")
	{
		m_pBurgerTime->LoadLevel1(m_GameMode, "Level3");
	}
	else if (SceneManager::GetInstance().GetActiveSceneName() == "Level3")
	{
		m_pBurgerTime->LoadLevel1(m_GameMode, "MainMenu");
	}
}
void dae::GameManager::ChangePlayer()
{

	auto& scene = SceneManager::GetInstance().GetActiveScene();

	auto& sceneObjects = scene.GetSceneObjects();
	bool pepperFound = false;
	for (auto& object : sceneObjects)
	{
		if (dynamic_cast<GameObject*>(object.get())->GetComponent<PeterPepperComponent>("PeterPepper"))
		{
			pepperFound = true;
			InputManager::GetInstance().SetPlayer(dynamic_cast<GameObject*>(object.get()), 0);
			InputManager::GetInstance().SetPlayer(nullptr, 1);
		}
	}

}
void dae::GameManager::ResetScene(bool fullReset)
{
	auto& scene = SceneManager::GetInstance().GetActiveScene();
	scene.MarkForDestroy();
	if (!fullReset)
	{
		LoadLevel("Same");
	}
	else
	{
		LoadLevel("MainMenu");
	}
	m_CompletedBurgers = 0;
	m_LevelComplete = false;
}