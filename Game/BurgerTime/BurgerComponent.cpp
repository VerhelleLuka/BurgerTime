#include "MiniginPCH.h"
#include "BurgerComponent.h"
#include "PeterPepper.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "PlatformComponent.h"
#include "Enemy.h"
dae::BurgerComponent::BurgerComponent()
	:m_Fall(false),
	m_Caught(false),
	m_LevelsToFall(0),
	m_StartFall(false)
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
	if (m_Fall && !m_Caught)
	{
		m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2{ 0, 100 });
	}
	m_StartFall = false;
}

void dae::BurgerComponent::ForceFall()
{
	for (int i{}; i < m_NrParts - 1; ++i)
	{
		m_WalkedOver[i] = true;
	}
	m_Fall = true;
	m_StartFall = true;
}
void dae::BurgerComponent::OnOverlap(RigidBodyComponent* other)
{
	if (other->GetParent()->GetTag() == "Enemy")
	{
		if (other->GetTransform().GetPosition().y > m_pParent->GetTransform().GetPosition().y && m_Fall)
		{
			if (other->GetParent()->GetComponent<Enemy>("Enemy")->GetEnemyType() == EnemyType::SAUSAGE && !other->GetParent()->GetComponent<Enemy>("Enemy")->IsDead())
			{
				m_pPeterPepper->AddPoints(100);
			}
			other->GetParent()->GetComponent<Enemy>("Enemy")->Kill();
		}
		if (!other->GetParent()->GetComponent<Enemy>("Enemy")->GetFalling())
		{
			if (other->GetTransform().GetPosition().y <= m_pParent->GetTransform().GetPosition().y && m_Fall && m_StartFall)
			{
				other->GetParent()->GetComponent<Enemy>("Enemy")->Fall();
				m_pPeterPepper->AddPoints(500);
				m_LevelsToFall++;
			}
		}
		//else if ((other->GetTransform().GetPosition().y <= m_pParent->GetTransform().GetPosition().y && m_Fall)
		//	{

		//	}
	}
	if (other->GetParent()->GetTag() == "Platform")
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
			if (m_LevelsToFall > 0)
			{
				ForceFall();
				m_LevelsToFall--;
			}
		}
	}
	if (other->GetParent()->GetTag() == "PeterPepper")
	{
		if (other->GetParent()->GetComponent<PeterPepperComponent>("PeterPepper").get() != m_pPeterPepper)
			m_pPeterPepper = other->GetParent()->GetComponent<PeterPepperComponent>("PeterPepper").get();
		for (int i{}; i < m_NrParts - 1; ++i)
		{

			if (other->GetParent()->GetTransform().GetPosition().x - 4 > m_xPositions[i]
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
				m_StartFall = m_AllTrue;
			}

		}

	}
	if (other->GetParent()->GetTag() == "Burger")
	{
		if (other->GetParent()->GetComponent<BurgerComponent>("BurgerComp")->GetCaught())
		{
			if (m_pParent->GetComponent<SpriteComponent>("BurgerSprite")->GetAnimationName() == "Top_bun" && !m_Caught)
			{
				GameManager::GetInstance().BurgerCompleted();
			}
			m_Caught = true;

		}
		else if (other->GetParent()->GetTransform().GetPosition().y < m_pParent->GetTransform().GetPosition().y)
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

