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

	}
}

void dae::Enemy::OnTriggerExit(RigidBodyComponent* /*other*/)
{

}