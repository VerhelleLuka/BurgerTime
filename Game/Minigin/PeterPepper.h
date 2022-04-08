#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "Subject.h"
#include "EventStructs.h"
#include "Achievements.h"
namespace dae
{

	// Defining our achievements
	enum EAchievements
	{
		ACH_WIN_ONE_GAME = 0,

	};
	class PeterPepperComponent final : public BaseComponent, public Subject
	{
	public:
		virtual void Update(float deltaTime) ;
		virtual void Render() const {};

		PeterPepperComponent(int lives, bool steamApi) ;
		virtual ~PeterPepperComponent() {};

		void ReduceLife();
		int GetLives() { return m_Lives; }
		void AddPoints(int points);
		int GetPoints(){return m_Points;}
	protected:
		GameObject* m_pParent{};

	private:
		int m_Lives;
		int m_Points;



		// Achievement array which will hold data about the achievements and their state
		Achievement_t m_Achievements[1] =
		{
			_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
		};
		CSteamAchievements* m_pSteamAchievements = NULL;

	};
}
