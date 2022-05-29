#include "Enemy.h"
#include "RigidBodyComponent.h"
#include "EnemyState.h"
#include "PlatformComponent.h"
#include "SpriteComponent.h"
dae::Enemy::Enemy()
	:m_pEnemyState(new MovingLeft())
{
}

dae::Enemy::~Enemy()
{
	delete m_pEnemyState;
}
void dae::Enemy::Initialize()
{
	m_pEnemyState->SetSprite(m_pParent->GetComponent<SpriteComponent>("EnemySprite").get());
	m_pEnemyState->SetRigidBody(m_pParent->GetComponent<RigidBodyComponent>("RigidBody").get());
}
void dae::Enemy::FixedUpdate(float /*elapsedTime*/)
{
	m_pEnemyState->Update();
}


void dae::Enemy::SetOverlapEvent()
{
	auto bindIng = std::bind(&Enemy::OnOverlap, this, std::placeholders::_1);
	m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetOnOverlapEvent(bindIng);
}

void dae::Enemy::SetOnTriggerExitEvent()
{
	auto bindIng = std::bind(&Enemy::OnTriggerExit, this, std::placeholders::_1);
	m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetOnTriggerExit(bindIng);
}

void dae::Enemy::OnOverlap(RigidBodyComponent* other)
{
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
		return;
	}
}

void dae::Enemy::OnTriggerExit(RigidBodyComponent* /*other*/)
{

}