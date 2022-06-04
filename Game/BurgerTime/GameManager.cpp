#include "GameManager.h"
#include "BurgerTime.h"
#include "BurgerTimeStructs.h"
#include <string>
#include "SceneManager.h"
#include "Subject.cpp"
dae::GameManager::GameManager()
	: m_pBurgerTime(nullptr),
	m_Points(0),
	m_NrBurgers(0),
	m_CompletedBurgers(0),
	m_CurrentLevelIndex(0)
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
	if (m_CompletedBurgers >= m_NrBurgers)
	{
		m_CompletedBurgers = 0;
		++m_CurrentLevelIndex;

		std::shared_ptr<EventArgs> emptyArgs = std::make_shared<EventArgs>();
		Notify(EventType::WIN,emptyArgs);
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
		m_pBurgerTime->LoadLevel1(m_GameMode, m_LevelNames[m_CurrentLevelIndex]);
	}
}