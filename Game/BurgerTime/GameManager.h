#pragma once
#include "Singleton.h"
#include <string>
#include "BurgerTimeStructs.h"
namespace dae
{

	class BurgerTime;
	class GameManager : public Singleton<GameManager>
	{
	public:
		GameManager(): m_pBurgerTime(nullptr), m_Points(0) {};
		~GameManager() = default;

		GameManager(const GameManager& other) = delete;
		GameManager(GameManager&& other) = delete;
		GameManager& operator=(const GameManager& other) = delete;
		GameManager& operator=(GameManager&& other) = delete;

		//void SetGameMode(GameMode gameMode) { m_GameMode = gameMode; }
		//GameMode GetGameMode() const { return m_GameMode; }

		void SetBurgerTimeGame(BurgerTime* burgerTime);
		void LoadLevel(const std::string& levelName, GameMode gameMode) const;
	private:
		int m_Points;
		BurgerTime* m_pBurgerTime;
		
	};
}