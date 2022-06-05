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
	m_LevelComplete(false)
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
void dae::GameManager::LoadLevel(bool incrementIndex)
{
	if (incrementIndex)
	{
		++m_CurrentLevelIndex;
	}
	if (m_pBurgerTime)
	{
		if (m_LevelComplete)
		{
			m_LevelComplete = false;
			m_CompletedBurgers = 0;
		}
		m_pBurgerTime->LoadLevel1(m_GameMode, m_LevelNames[m_CurrentLevelIndex]);

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
			InputManager::GetInstance().SetPlayer(nullptr,1);
		}
	}

}
void dae::GameManager::ResetScene(bool fullReset)
{
	auto& scene = SceneManager::GetInstance().GetActiveScene();
	scene.SetEmpty(true);
	auto& sceneObjects = scene.GetSceneObjects();

	for (auto& object : sceneObjects)
	{
		if (dynamic_cast<GameObject*>(object.get())->GetComponent<PeterPepperComponent>("PeterPepper"))
		{
			dynamic_cast<GameObject*>(object.get())->SetTransform(dynamic_cast<GameObject*>(object.get())->GetComponent<PeterPepperComponent>("PeterPepper")->GetSpawnPos().x,
				dynamic_cast<GameObject*>(object.get())->GetComponent<PeterPepperComponent>("PeterPepper")->GetSpawnPos().y, 0.f);
		}
		else if (dynamic_cast<GameObject*>(object.get())->GetComponent<Enemy>("Enemy"))
		{
			dynamic_cast<GameObject*>(object.get())->GetComponent<Enemy>("Enemy")->Kill();
		}
		else if (dynamic_cast<GameObject*>(object.get())->GetTag() == "Enemy")
		{
			dynamic_cast<GameObject*>(object.get())->GetComponent<Enemy>("Enemy")->Kill();
		}

		if (fullReset)
		{
			dynamic_cast<GameObject*>(object.get())->MarkForDelete();
		}
	}
	if (fullReset)
	{
		m_CompletedBurgers = 0;
	}
}