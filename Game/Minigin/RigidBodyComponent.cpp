#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "Structs.h"

//Stuff you can put in a rigidbodycomponent
void dae::RigidBodyComponent::SetDirection(Float2 direction)
{
	m_Direction = direction;
}

void dae::RigidBodyComponent::Update(float elapsedSec)
{
	if (abs(m_Direction.x) > 0.01f || abs(m_Direction.y) > 0.01f)
	{
		m_pParent->SetTransform(m_pParent->GetTransform().GetPosition().x + m_Direction.x * elapsedSec,
			m_pParent->GetTransform().GetPosition().y + m_Direction.y * elapsedSec,
			m_pParent->GetTransform().GetPosition().z);
	}

}
