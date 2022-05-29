#include "EnemyState.h"
#include "RigidBodyComponent.h"
#include "Enemy.h"
#include "SpriteComponent.h"
void dae::MovingDown::Update()
{
	if (m_pEnemy->GetCanDescend())
	{
		m_pRigidBody->SetDirection(Float2{ 0.f, 50.f });
		m_pSprite->SetActiveAnimation("Descend");

	}
}
void dae::MovingUp::Update()
{
	if (m_pEnemy->GetCanClimb())
	{
		m_pRigidBody->SetDirection(Float2{ 0.f, -50.f });
		m_pSprite->SetActiveAnimation("Climb");
	}
}
void dae::MovingLeft::Update()
{
	if (m_pEnemy->GetCanWalkLeft())
	{
		m_pRigidBody->SetDirection(Float2{ -50.f, 0.f });
		m_pSprite->SetActiveAnimation("WalkLeft");

	}
}

void dae::MovingRight::Update()
{
	if (m_pEnemy->GetCanWalkRight())
	{
		m_pRigidBody->SetDirection(Float2{ 50.f, 0.f });
		m_pSprite->SetActiveAnimation("WalkRight");

	}
}