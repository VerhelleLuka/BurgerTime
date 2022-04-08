#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "PointsDisplayComponent.h"
dae::PeterPepperComponent::PeterPepperComponent(int lives, bool steamApi)
	:m_Lives(lives)
	,m_Points(0)
	
{
	if(steamApi)
		m_pSteamAchievements = new CSteamAchievements(m_Achievements, 1);
}

void dae::PeterPepperComponent::Update(float elapsedSec)
{
	elapsedSec = 0;

}

void dae::PeterPepperComponent::AddPoints(int points)
{
	m_Points += points;
	std::shared_ptr<PointsEventArgs> args = std::make_shared<PointsEventArgs>();
	args->points = m_Points;
	Notify(EventType::GAINEDPOINTS, args);

	if (m_Points >= 500)
	{
		m_pSteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
	}

}

void dae::PeterPepperComponent::ReduceLife()
{
	if (m_Lives > 0)
	{
		std::shared_ptr<EventArgs> emptyArgs = std::make_shared<EventArgs>();;
		m_Lives--;
		Notify(EventType::LOSTLIFE, emptyArgs);
	}
}

