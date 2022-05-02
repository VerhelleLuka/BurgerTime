#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "PointsDisplayComponent.h"
#include "SpriteComponent.h"
#include "Sound.h"
dae::PeterPepperComponent::PeterPepperComponent(int lives, bool /*steamApi*/)
	:m_Lives(lives)
	,m_Points(0)
	,m_State(PeterPepperState::Climb)
	
{
	//if(steamApi)
	//	m_pSteamAchievements = new CSteamAchievements(m_Achievements, 1);
}

void dae::PeterPepperComponent::Update(float /*elapsedSec*/)
{
}

void dae::PeterPepperComponent::AddPoints(int points)
{
	
	//ServiceLocator::GetSoundSystem();
	
	m_Points += points;
	std::shared_ptr<PointsEventArgs> args = std::make_shared<PointsEventArgs>();
	ServiceLocator::GetSoundSystem().Play(0, 100);

	args->points = m_Points;
	Notify(EventType::GAINEDPOINTS, args);

	//if (m_Points >= 500)
	//{
	//	m_pSteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
	//}

}

void dae::PeterPepperComponent::ReduceLife()
{
	ServiceLocator::GetSoundSystem().Play(1, 100);
	if (m_Lives > 0)
	{
		std::shared_ptr<EventArgs> emptyArgs = std::make_shared<EventArgs>();
		m_Lives--;
		Notify(EventType::LOSTLIFE, emptyArgs);
	}
}

void dae::PeterPepperComponent::ChangeState(int state = 0)
{
	m_State = static_cast<PeterPepperState>(state);
	std::shared_ptr<SpriteEventArgs> args = std::make_shared<SpriteEventArgs>();
	switch (m_State)
	{

	case PeterPepperState::RunRight:
		args->name = "RunRight";
		break;
	case PeterPepperState::RunLeft:
		args->name = "RunLeft";
		break;
	case PeterPepperState::Climb:
		args->name = "Climb";
		break;
	case PeterPepperState::Descend:
		args->name = "Descend";
		break;
	default:
		args->name = "Idle";
		break;
	}
	Notify(EventType::STATECHANGED, args);

}

