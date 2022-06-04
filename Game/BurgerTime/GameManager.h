#pragma once
#include "Singleton.h"
#include <string>
#include "BurgerTimeStructs.h"
#include <vector>
#include "Subject.h"
namespace dae
{

	class BurgerTime;
	class GameManager : public Singleton<GameManager>, public Subject
	{
	public:
		GameManager();
		~GameManager() = default;

		GameManager(const GameManager& other) = delete;
		GameManager(GameManager&& other) = delete;
		GameManager& operator=(const GameManager& other) = delete;
		GameManager& operator=(GameManager&& other) = delete;

		void SetBurgerTimeGame(BurgerTime* burgerTime);
		void LoadLevel( bool incrementIndex) ;

		void SetNrOfBurgers(int nrBurgers) { m_NrBurgers = nrBurgers; }
		void ResetCompletedBurgers() { m_CompletedBurgers = 0; }
		void BurgerCompleted();

		int GetLevelIndex() const { return m_CurrentLevelIndex;}
		void AddPoints(int points) { m_Points += points;}
		int GetPoints() const { return m_Points; }

		void SetGameMode(GameMode gameMode) { m_GameMode = gameMode; }

	private:
		int m_Points;
		BurgerTime* m_pBurgerTime;
		GameMode m_GameMode;
		int m_NrBurgers;
		int m_CompletedBurgers;

		std::vector<std::string> m_LevelNames;
		int m_CurrentLevelIndex;
		
	};
}