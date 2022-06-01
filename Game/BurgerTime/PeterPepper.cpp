#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "PointsDisplayComponent.h"
#include "SpriteComponent.h"
#include "Sound.h"
#include "PlatformComponent.h"
#include "Animation.h"
#include "LadderComponent.h"
#include "SceneManager.h"
#include "Scene.h"
dae::PeterPepperComponent::PeterPepperComponent(int lives)
	:m_Lives(lives)
	, m_Points(0)
	, m_State(PeterPepperState::Climb)
	, m_OverlappingLadder(false),
	m_OverlappingPlatform(false)
	, m_CanClimb(false)
	, m_CanDescend(false)
	, m_CanWalkLeft(false)
	, m_CanWalkRight(false)
	, m_InMenu(true)
	, m_OverlappingButton(false)
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

	if (!m_InMenu)
	{
		return;
	}
	//m_OverlappingButton = false;

	m_CanWalkLeft = true;
	m_CanWalkRight = true;
	m_CanClimb = true;
	m_CanDescend = true;
	if (m_pParent->GetTransform().GetPosition().x < 0)
	{
		m_CanWalkLeft = false;
	}
	//640 is the window width
	//480 is the platform height
	if (m_pParent->GetTransform().GetPosition().x + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetWidth() > 640)
	{
		m_CanWalkRight = false;
	}
	if (m_pParent->GetTransform().GetPosition().y < 0)
	{
		m_CanClimb = false;
	}
	if (m_pParent->GetTransform().GetPosition().y + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetHeight() > 480)
	{
		m_CanDescend = false;
	}
}

void dae::PeterPepperComponent::FixedUpdate(float /*elapsedSec*/)
{
	if (m_InMenu)
		return;
	auto overlappingBodies = m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetOverlappingBodies();
	bool isOverlappingPlatform = false;
	for (int i{}; i < overlappingBodies.size(); ++i)
	{
		if (overlappingBodies[i]->GetParent()->GetComponent<PlatformComponent>("PlatformComp"))
		{
			isOverlappingPlatform = true;
		}
	}
	if (!isOverlappingPlatform)
	{
		m_CanWalkLeft = false;
		m_CanWalkRight = false;
	}

}
void dae::PeterPepperComponent::AddPoints(int points)
{
	m_Points += points;
	std::shared_ptr<PointsEventArgs> args = std::make_shared<PointsEventArgs>();

	args->points = m_Points;
	Notify(EventType::GAINEDPOINTS, args);
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
void dae::PeterPepperComponent::ButtonPress()
{
	if (m_OverlappingButton)
	{
		std::shared_ptr<EventArgs> emptyArgs = std::make_shared<EventArgs>();
		Notify(EventType::LOADLEVEL, emptyArgs);
	}
}
void dae::PeterPepperComponent::OnOverlap(RigidBodyComponent* other)
{
	if (other->GetParent())
	{
		if (other->GetParent()->GetComponent<ButtonComponent>("ButtonComp"))
		{
			m_OverlappingButton = true;
			return;
		}
		//if the other overlap is a platform
		if (other->GetParent()->GetComponent<PlatformComponent>("PlatformComp"))
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
			return;
		}


		//if it's a ladder
		if (other->GetParent()->GetComponent<LadderComponent>("LadderComp"))
		{
			m_CanClimb = false;
			m_CanDescend = false;
			Float2 ladderPos = { other->GetTransform().GetPosition().x, other->GetTransform().GetPosition().y };
			float ladderHeight = other->GetHeight();
			//8 is a ladder offset
			if (m_pParent->GetTransform().GetPosition().y >= (ladderPos.y - ladderHeight / 2) - 8 ||
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
		return;
	}
	else
	{
		m_CanDescend = false;
		m_CanClimb = false;
	}
}

void dae::PeterPepperComponent::OnTriggerExit(RigidBodyComponent* other)
{
	if (other->GetParent()->GetComponent<LadderComponent>("LadderComp"))
	{
		m_CanDescend = false;
		m_CanClimb = false;
	}
	if (other->GetParent()->GetComponent<ButtonComponent>("ButtonComp"))
	{
		m_OverlappingButton = false;
	}
}