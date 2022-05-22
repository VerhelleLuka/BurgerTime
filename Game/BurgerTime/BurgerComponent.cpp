#include "MiniginPCH.h"
#include "BurgerComponent.h"
#include "PeterPepper.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "PlatformComponent.h"
dae::BurgerComponent::BurgerComponent()
	:m_Fall(false)
{

}

void dae::BurgerComponent::Initialize()
{
	for (int i{}; i < m_NrParts; ++i)
	{
		m_xPositions[i] = m_pParent->GetTransform().GetPosition().x + (m_pParent->GetComponent<SpriteComponent>("BurgerSprite")->GetAnimation().GetScaledWidth() * i) / 5;
	}
}
void dae::BurgerComponent::FixedUpdate(float /*elapsedSec*/)
{
	if (m_Fall == true)
	{
		m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2{ 0, 100 });
	}
	//std::cout << m_WalkedOver[0] << " " << m_WalkedOver[1] << " " << m_WalkedOver[2] << " " << m_WalkedOver[3] << "\n";
}

void dae::BurgerComponent::ForceFall()
{
	for (int i{}; i < m_NrParts - 1; ++i)
	{
		m_WalkedOver[i] = true;
	}
	m_Fall = true;
}
void dae::BurgerComponent::OnOverlap(RigidBodyComponent* other)
{
	if (other->GetParent()->GetComponent<PlatformComponent>("PlatformComp"))
	{
		if (m_pPlatformComp.get() == nullptr)
		{
			m_pPlatformComp = other->GetParent()->GetComponent<PlatformComponent>("PlatformComp");
		}
		if (m_Fall && other->GetParent()->GetComponent<PlatformComponent>("PlatformComp") != m_pPlatformComp)
		{
			m_pPlatformComp = other->GetParent()->GetComponent<PlatformComponent>("PlatformComp");
			m_Fall = false;
			if (m_pPeterPepper != nullptr)
			{
				m_pPeterPepper->AddPoints(50);
			}
			for (int i{}; i < m_NrParts - 1; ++i)
			{
				m_WalkedOver[i] = false;
			}
		}
	}
	if (other->GetParent()->GetComponent<PeterPepperComponent>("PeterPepper"))
	{
		if (other->GetParent()->GetComponent<PeterPepperComponent>("PeterPepper").get())
			m_pPeterPepper = other->GetParent()->GetComponent<PeterPepperComponent>("PeterPepper").get();
		for (int i{}; i < m_NrParts - 1; ++i)
		{

			if (other->GetParent()->GetTransform().GetPosition().x > m_xPositions[i]
				&& other->GetParent()->GetTransform().GetPosition().x < m_xPositions[i + 1])
			{
				m_WalkedOver[i] = true;
				bool m_AllTrue = true;
				for (int j{}; j < m_NrParts - 1; ++j)
				{
					if (m_WalkedOver[j] == false)
					{
						m_AllTrue = false;
					}
				}

				m_Fall = m_AllTrue;
			}

		}

	}
	if (other->GetParent()->GetComponent<BurgerComponent>("BurgerComp"))
	{
		if (other->GetParent()->GetTransform().GetPosition().y < m_pParent->GetTransform().GetPosition().y)
		{
			m_pPeterPepper = other->GetParent()->GetComponent<BurgerComponent>("BurgerComp")->GetPeterPepper();

			ForceFall();
		}
		else
		{
			other->GetParent()->GetComponent<BurgerComponent>("BurgerComp")->SetPeterPepper(m_pPeterPepper);

			other->GetParent()->GetComponent<BurgerComponent>("BurgerComp")->ForceFall();
		}
	}
}

