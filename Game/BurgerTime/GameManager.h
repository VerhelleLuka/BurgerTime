#pragma once
#include "Singleton.h"
#include <string>
#include "BurgerTimeStructs.h"
#include <vector>
#include "Subject.h"
#include "Structs.h"
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
		void LoadLevel( const std::string& levelName) ;

		void SetNrOfBurgers(int nrBurgers) { m_NrBurgers = nrBurgers; }
		void ResetCompletedBurgers() { m_CompletedBurgers = 0; }
		void BurgerCompleted();

		int GetLevelIndex() const { return m_CurrentLevelIndex;}

		void SetGameMode(GameMode gameMode) { m_GameMode = gameMode; }
		void SetEnemySpawns(std::vector<Float2> enemySpawns) { m_EnemySpawnPositions = enemySpawns; }
		void ResetScene(bool fullReset);
		void ChangePlayer();
		GameMode GetGameMode() const { return m_GameMode; }

		void ReduceLife(bool isToRefresh);
		int GetLives() const { return m_Lives; }

		void AddPoints(int points);
		int GetPoints() const { return m_Points; }

	private:
		int m_Points;
		int m_Lives;
		BurgerTime* m_pBurgerTime;
		GameMode m_GameMode;
		int m_NrBurgers;
		int m_CompletedBurgers;

		std::vector<std::string> m_LevelNames;
		std::vector<Float2> m_EnemySpawnPositions;
		int m_CurrentLevelIndex;

		bool m_LevelComplete;
		
	};
}