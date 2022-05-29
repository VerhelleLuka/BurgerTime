#include "EnemyState.h"
#include "RigidBodyComponent.h"

void dae::MovingDown::Update()
{
	m_pRigidBody->SetDirection(Float2{ 0.f, 50.f });
}
void dae::MovingUp::Update()
{
	m_pRigidBody->SetDirection(Float2{ 0.f, -50.f });
}
void dae::MovingLeft::Update()
{
	m_pRigidBody->SetDirection(Float2{ -50.f, 0.f });
}

void dae::MovingRight::Update()
{
	m_pRigidBody->SetDirection(Float2{ 50.f, 0.f });
}