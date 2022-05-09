#include "MiniginPCH.h"
#include "Physics.h"


void dae::Physics::FixedUpdate(float /*deltaTime*/)
{
	CheckOverlap();
}

void dae::Physics::AddRigidBodyComponent(std::shared_ptr<RigidBodyComponent>rigidBody)
{
	m_pRigidBodies.push_back(rigidBody);
	//AddObserver(rigidBody.get());
}

void dae::Physics::CheckOverlap()
{
	//Overlap check for players/AI on ladders
	for (size_t i{}; i < m_pRigidBodies.size(); ++i)
	{
		for (auto& rigidBody : m_pRigidBodies)
		{
			if (rigidBody != m_pRigidBodies[i])
			{
				//If at least one of the rigidbodies is a trigger
				if (rigidBody->GetTrigger() || m_pRigidBodies[i]->GetTrigger())
				{
					//This is super specific code for PeterPepper/Enemy overlap with stairs

					//Every sprite is 32 pixels wide (16px source *  2 scale)
					//The overlap with the ladder should be the center of the ladder (16px) with,
					//the utmost left position they should be able to climb up on is 10 and utmost right 22
					//so
					Float2 posA = { rigidBody->GetTransform().GetPosition().x, rigidBody->GetTransform().GetPosition().y };
					Float2 posB = { m_pRigidBodies[i]->GetTransform().GetPosition().x, m_pRigidBodies[i]->GetTransform().GetPosition().y };
					//float widthA = rigidBody->GetWidth();
					float widthB = m_pRigidBodies[i]->GetWidth();
					//float heightA = rigidBody->GetHeight();
					float heightB = m_pRigidBodies[i]->GetHeight();

					//check overlap

					//check widths
					if (posA.x <= posB.x + widthB && posA.x >= posB.x)
					{
						//check heights
						if (posA.y <= posB.y + heightB && posA.y >= posB.y)
						{
							if (m_pRigidBodies[i]->GetTrigger())
							{
								m_pRigidBodies[i]->OnOverlap(rigidBody.get());
							}
							if (rigidBody->GetTrigger())
							{
								rigidBody->OnOverlap(m_pRigidBodies[i].get());
							}
						}
					}

				}
			}
		}
	}
}