#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "PointsDisplayComponent.h"
#include "SpriteComponent.h"
#include "Sound.h"
dae::PeterPepperComponent::PeterPepperComponent(int lives, bool /*steamApi*/)
	:m_Lives(lives)
	, m_Points(0)
	, m_State(PeterPepperState::Climb)
{
	//if(steamApi)
	//	m_pSteamAchievements = new CSteamAchievements(m_Achieve 

	//m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetOnOverlapEvent<PeterPepperComponent>((&PeterPepperComponent::OnOverlap), this);

} 

void dae::PeterPepperComponent::Update(float /*elapsedSec*/)
{
}

void dae::PeterPepperComponent::AddPoints(int points)
{

	//ServiceLocator::GetSoundSystem();

	m_Points += points;
	std::shared_ptr<PointsEventArgs> args = std::make_shared<PointsEventArgs>();

	args->points = m_Points;
	Notify(EventType::GAINEDPOINTS, args);

	//if (m_Points >= 500)
	//{
	//	m_pSteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
	//}

}

void dae::PeterPepperComponent::ReduceLife()
{
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

void dae::PeterPepperComponent::OnOverlap(RigidBodyComponent* other)
{
	if (other->GetParent())
	{
		//if the other overlap is a platform
		if (other->GetParent()->GetComponent<RigidBodyComponent>("PlatformRigidBody"))
		{
			std::cout << "Overlap platform\n";
		}
		//if it's a ladder
		if (other->GetParent()->GetComponent<RigidBodyComponent>("LadderRigidBody"))
		{
			std::cout << "Overlap ladders\n";

		}
	}
}