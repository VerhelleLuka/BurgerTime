#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "Structs.h"
dae::RigidBodyComponent::RigidBodyComponent(float width, float height, bool isTrigger)
	:m_pTransform(&m_pParent->GetTransform()) ,
	m_Width(width),
	m_Height(height),
	m_IsTrigger(isTrigger),
	m_OverlapEvent(),
	m_PositionOffset(Float2{ 0.f,0.f })
{

}
//
void dae::RigidBodyComponent::SetDirection(Float2 direction)
{
	m_Direction = direction;
	m_LastDirection = direction;
}

void dae::RigidBodyComponent::Update(float /*elapsedSec*/)
{

}


void dae::RigidBodyComponent::FixedUpdate(float elapsedSec)
{
	if (abs(m_Direction.x) > 0.01f || abs(m_Direction.y) > 0.01f)
	{
		m_pParent->SetTransform(m_pParent->GetTransform().GetPosition().x + m_Direction.x * elapsedSec,
			m_pParent->GetTransform().GetPosition().y + m_Direction.y * elapsedSec,
			m_pParent->GetTransform().GetPosition().z);
		m_Direction = { 0.f,0.f };
	}

}
void dae::RigidBodyComponent::Reverse(float elapsedSec)
{
	m_pParent->SetTransform(m_pParent->GetTransform().GetPosition().x + m_LastDirection.x * elapsedSec,
		m_pParent->GetTransform().GetPosition().y + m_LastDirection.y * elapsedSec,
		m_pParent->GetTransform().GetPosition().z);
}

void dae::RigidBodyComponent::OnOverlap(RigidBodyComponent* other)
{
	if (m_OverlapEvent != nullptr)
	{
		m_OverlapEvent(other);
	}
}

