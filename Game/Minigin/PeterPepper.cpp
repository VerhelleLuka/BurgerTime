#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "PointsDisplayComponent.h"
#include "SpriteComponent.h"
#include "Sound.h"
#include "PlatformComponent.h"
#include "Animation.h"
#include "LadderComponent.h"
dae::PeterPepperComponent::PeterPepperComponent(int lives, bool /*steamApi*/)
	:m_Lives(lives)
	, m_Points(0)
	, m_State(PeterPepperState::Climb)
	, m_OverlappingLadder(false),
	m_OverlappingPlatform(false)
	,m_CanClimb(false)
	,m_CanDescend(false)
	,m_CanWalkLeft(false)
	,m_CanWalkRight(false)
{
	//if(steamApi)
	//	m_pSteamAchievements = new CSteamAchievements(m_Achieve 

	//m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetOnOverlapEvent<PeterPepperComponent>((&PeterPepperComponent::OnOverlap), this);

}

void dae::PeterPepperComponent::Update(float elapsedSec)
{
	if (!m_CanClimb && !m_CanDescend && !m_CanWalkLeft && !m_CanWalkRight)
	{
		m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->Reverse(elapsedSec);
	}
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
			m_CanWalkLeft = false;
			m_CanWalkRight = false;
			Float2 platformPos = { other->GetTransform().GetPosition().x, other->GetTransform().GetPosition().y };
			float platformWidth = other->GetWidth();
			if (m_pParent->GetTransform().GetPosition().y + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetHeight() - 5 < platformPos.y)
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
			if (m_pParent->GetTransform().GetPosition().y + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetHeight() - 5 < platformPos.y)
				m_CanWalkRight = true;

			//IF there is no platform left to this one
			if (!other->GetParent()->GetComponent<PlatformComponent>("PlatformComp")->GetHasNext())
			{
				//And the overlap is at its end
				if ((m_pParent->GetTransform().GetPosition().x + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetWidth()) >= (platformPos.x + (platformWidth)))
				{
					m_CanWalkRight = false;
				}
			}
		}


		//if it's a ladder
		if (other->GetParent()->GetComponent<RigidBodyComponent>("LadderRigidBody"))
		{
			m_CanClimb = false;
			m_CanDescend = false;
			Float2 ladderPos = { other->GetTransform().GetPosition().x, other->GetTransform().GetPosition().y };
			float ladderHeight = other->GetHeight();
			if (m_pParent->GetTransform().GetPosition().y  >= ladderPos.y - ladderHeight / 2 ||
				other->GetParent()->GetComponent<LadderComponent>("LadderComp")->GetHasUp())
			{
				m_CanClimb = true;
			}
			//std::cout << other->GetParent()->GetComponent<LadderComponent>("LadderComp")->GetHasUp() << "<-- Has up |Has down -->" << other->GetParent()->GetComponent<LadderComponent>("LadderComp")->GetHasDown() << "\n";
			if (m_pParent->GetTransform().GetPosition().y + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetHeight() + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetOffset().y <= ladderPos.y + ladderHeight /*||
				other->GetParent()->GetComponent<LadderComponent>("LadderComp")->GetHasDown()*/)
			{
				m_CanDescend = true;
			}
		}
	}
	else
	{
		m_CanDescend = false;
		m_CanClimb = false;
	}
}
