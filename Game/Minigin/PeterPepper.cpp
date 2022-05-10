#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "PointsDisplayComponent.h"
#include "SpriteComponent.h"
#include "Sound.h"
#include "PlatformComponent.h"
#include "Animation.h"
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
			std::cout << "Is overlapping";

			Float2 platformPos = { other->GetTransform().GetPosition().x, other->GetTransform().GetPosition().y };
			float platformWidth = other->GetWidth();
			m_CanWalkLeft = true;

			//IF there is no platform left to this one
			if (!other->GetParent()->GetComponent<PlatformComponent>("PlatformComp")->GetHasPrevious())
			{
				//And the overlap is at its end
				if (m_pParent->GetTransform().GetPosition().x < platformPos.x)
				{
					m_CanWalkLeft = false;
				}
			}
			m_CanWalkRight = true;
			//IF there is no platform left to this one

			//And the overlap is at its end
			if (!other->GetParent()->GetComponent<PlatformComponent>("PlatformComp")->GetHasNext())
			{
				std::cout << "DOES NOT HAVE NEXT\n";
				if (m_pParent->GetTransform().GetPosition().x /*+ m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetWidth())*/ >= (platformPos.x + (platformWidth / 2.f)))
				{
					std::cout << "IS AT THE END OF PLATFORM\n";
					m_CanWalkRight = false;
				}
			}
		}
		//if it's a ladder
		if (other->GetParent()->GetComponent<RigidBodyComponent>("LadderRigidBody"))
		{
			m_CanClimb = true;
			//Float2 ladderPos = { other->GetTransform().GetPosition().x, other->GetTransform().GetPosition().y };
			////float ladderHeight = other->GetHeight();
			//if (m_pParent->GetTransform().GetPosition().y >= ladderPos.y)
			//{
			//	m_CanClimb = false;
			//}
		}
	}

}
