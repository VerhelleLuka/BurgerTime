#include "GameManager.h"
#include "BurgerTime.h"
#include "BurgerTimeStructs.h"
#include <string>
void dae::GameManager::SetBurgerTimeGame(BurgerTime* burgerTime)
{
	m_pBurgerTime = burgerTime;
}
//
void dae::GameManager::LoadLevel(const std::string& levelName, GameMode gameMode) const
{
	if (levelName == "Level1")
	{
		if(m_pBurgerTime)
		m_pBurgerTime->LoadLevel1(gameMode);
	}
	else if (levelName == "Level2")
	{
		if (m_pBurgerTime)
			m_pBurgerTime->LoadLevel2(gameMode);

	}
	else if (levelName == "Level3")
	{
		if (m_pBurgerTime)
			m_pBurgerTime->LoadLevel3(gameMode);

	}
}