#include "MiniginPCH.h"
#include "Physics.h"


void dae::Physics::FixedUpdate(float /*deltaTime*/)
{
	//Overlap check for players/AI on ladders
	for (int i{}; i < m_pRigidBodies.size(); ++i)
	{
		for (auto& rigidBody : m_pRigidBodies)
		{
			if (rigidBody != m_pRigidBodies[i])
			{
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
					//float heightB = m_pRigidBodies[i]->GetHeight();

					//check overlap

					//check widths (for ladders)
					if (posA.x <= posB.x + widthB && posA.x >= posB.x)
					{
						//check heights for platforms, only needs to be the feet with a 4px offset
						if (posA.y <= posB.y + 4.f && posA.y >= posB.y)
						{
						}
					}
					//check if peter pepper component
				
				}
			}
		}
	}
}

void dae::Physics::AddRigidBodyComponent(std::shared_ptr<RigidBodyComponent>rigidBody)
{
	m_pRigidBodies.push_back(rigidBody);
	//AddObserver(rigidBody.get());
}
