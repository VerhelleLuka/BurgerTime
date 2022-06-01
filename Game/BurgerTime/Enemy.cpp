#include "Enemy.h"
#include "RigidBodyComponent.h"
#include "EnemyState.h"
#include "PlatformComponent.h"
#include "SpriteComponent.h"
#include "LadderComponent.h"
dae::Enemy::Enemy(EnemyType type)
	:m_pEnemyState(new MovingLeft()),
	m_Initialized(false),
	m_SwitchBehavior(false),
	m_BehaviorSwitchTime(0.f),
	m_CanClimb(false),
	m_CanDescend(false),
	m_CanWalkLeft(false),
	m_CanWalkRight(false),
	m_EnemyType(type)
{
}

dae::Enemy::~Enemy()
{
	delete m_pEnemyState;
}
void dae::Enemy::Initialize(Scene& scene)
{
	m_IsDead = false;
	m_pEnemyState->SetSprite(m_pParent->GetComponent<SpriteComponent>("EnemySprite").get());
	m_pEnemyState->SetRigidBody(m_pParent->GetComponent<RigidBodyComponent>("RigidBody").get());
	m_pEnemyState->SetEnemy(this);

	m_pEnemyState->SetClimbing(false);
	m_pEnemyState->SetWalking(true);
	if (!m_Initialized)
	{
		auto sceneObjects = scene.GetSceneObjects();
		for (int i = 0; i < sceneObjects.size(); ++i)
		{
			if (dynamic_cast<GameObject*>(sceneObjects[i].get())->GetComponent<PeterPepperComponent>("PeterPepper").get())
			{
				m_pPeter1Transform = &dynamic_cast<GameObject*>(sceneObjects[i].get())->GetTransform();
			}
		}
	}
	m_Initialized = true;
}


void dae::Enemy::FixedUpdate(float /*elapsedTime*/)
{
	m_pEnemyState->Update();
}

void dae::Enemy::Kill()
{
	m_IsDead = true;
	delete m_pEnemyState;
	m_pEnemyState = new Dying;
	Reinitialize();
}
void dae::Enemy::Update(float elapsedTime)
{
	if (m_SwitchBehavior)
	{
		m_BehaviorSwitchTime += elapsedTime;
		if (m_BehaviorSwitchTime > m_BehaviorSwitchTimer)
		{
			m_SwitchBehavior = false;
			m_BehaviorSwitchTime = 0.f;
		}
	}
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
	if (!m_IsDead)
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

			if (!m_pEnemyState->GetClimbing() || m_SwitchBehavior)
			{
				return;
			}

			if (m_pPeter1Transform->GetPosition().x >= m_pParent->GetTransform().GetPosition().x && m_CanWalkRight)
			{
				if (m_pEnemyState)
				{
					delete m_pEnemyState;
					m_pEnemyState = new MovingRight();
					Reinitialize();
					m_pEnemyState->SetClimbing(false);
					m_pEnemyState->SetWalking(true);
					m_SwitchBehavior = true;
				}

			}
			else if (m_CanWalkLeft)
			{
				if (m_pEnemyState)
				{
					m_SwitchBehavior = true;
					delete m_pEnemyState;
					m_pEnemyState = new MovingLeft();
					Reinitialize();
					m_pEnemyState->SetClimbing(false);
					m_pEnemyState->SetWalking(true);
				}

			}

		}
		if (other->GetParent()->GetComponent<RigidBodyComponent>("LadderRigidBody"))
		{
			m_pWalkedLadder = other->GetParent()->GetComponent<LadderComponent>("Ladder").get();
			Float2 ladderPos = { other->GetTransform().GetPosition().x, other->GetTransform().GetPosition().y };
			float ladderHeight = other->GetHeight();
			float ladderWidth = other->GetWidth();
			if (m_pParent->GetTransform().GetPosition().x < other->GetTransform().GetPosition().x + ladderWidth / 2 &&
				m_pParent->GetTransform().GetPosition().x + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetWidth() / 2 >= ladderPos.x)
			{
				m_CanClimb = false;
				m_CanDescend = false;
				//8 is a ladder offset
				if (m_pParent->GetTransform().GetPosition().y >= (ladderPos.y - ladderHeight / 2) - 8 ||
					other->GetParent()->GetComponent<LadderComponent>("LadderComp")->GetHasUp())
				{
					m_CanClimb = true;
				}
				if (m_pParent->GetTransform().GetPosition().y + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetHeight() + m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->GetOffset().y <= ladderPos.y + ladderHeight)
				{
					m_CanDescend = true;
				}

				if ((!m_pEnemyState->GetWalking() || m_SwitchBehavior) && m_pWalkedLadder == other->GetParent()->GetComponent<LadderComponent>("Ladder").get())
				{
					return;
				}
				if (m_pPeter1Transform->GetPosition().y >= m_pParent->GetTransform().GetPosition().y && m_CanDescend)
				{
					if (m_pEnemyState)
					{
						delete m_pEnemyState;
						m_pEnemyState = new MovingDown();
						Reinitialize();
						m_pEnemyState->SetClimbing(true);
						m_pEnemyState->SetWalking(false);
						m_SwitchBehavior = true;
					}

				}
				else if (m_CanClimb)
				{
					if (m_pEnemyState)
					{
						delete m_pEnemyState;
						m_pEnemyState = new MovingUp();
						Reinitialize();
						m_pEnemyState->SetClimbing(true);
						m_pEnemyState->SetWalking(false);
						m_SwitchBehavior = true;

					}
				}
			}
		}
	}

}

void dae::Enemy::OnTriggerExit(RigidBodyComponent* /*other*/)
{

}

void dae::Enemy::Reinitialize()
{
	m_pEnemyState->SetSprite(m_pParent->GetComponent<SpriteComponent>("EnemySprite").get());
	m_pEnemyState->SetEnemy(this);
	m_pEnemyState->SetRigidBody(m_pParent->GetComponent<RigidBodyComponent>("RigidBody").get());
}
