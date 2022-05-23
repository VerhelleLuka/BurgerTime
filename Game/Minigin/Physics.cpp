#include "MiniginPCH.h"
#include "Physics.h"


void dae::Physics::FixedUpdate(float /*deltaTime*/)
{
	CheckOverlap();
}

void dae::Physics::AddRigidBodyComponent(std::shared_ptr<RigidBodyComponent>rigidBody)
{
	
	if (int(m_pRigidBodies.size() - 1) < m_SceneNr)
	{
		std::vector<std::shared_ptr<RigidBodyComponent>> newSceneVector;
		newSceneVector.push_back(rigidBody);
		m_pRigidBodies.push_back(newSceneVector);
		return;
	}
	m_pRigidBodies[m_SceneNr].push_back(rigidBody);
	//AddObserver(rigidBody.get());
}
void dae::Physics::SetSceneNr(int sceneNr)
{
	m_SceneNr = sceneNr;
}
void dae::Physics::CheckOverlap()
{
	//Overlap check for players/AI on ladders
	for (size_t i{}; i < m_pRigidBodies[m_SceneNr].size(); ++i)
	{
		for (auto& rigidBody : m_pRigidBodies[m_SceneNr])
		{
			if (rigidBody != m_pRigidBodies[m_SceneNr][i])
			{
				//If at least one of the rigidbodies is a trigger
				if (rigidBody->GetTrigger() || m_pRigidBodies[m_SceneNr][i]->GetTrigger())
				{
					//This is super specific code for PeterPepper/Enemy overlap with stairs

					//Every sprite is 32 pixels wide (16px source *  2 scale)
					//The overlap with the ladder should be the center of the ladder (16px) with,
					//the utmost left position they should be able to climb up on is 10 and utmost right 22
					//so
					Float2 posA = { rigidBody->GetTransform().GetPosition().x ,
						rigidBody->GetTransform().GetPosition().y };
					Float2 posB = { m_pRigidBodies[m_SceneNr][i]->GetTransform().GetPosition().x,
						m_pRigidBodies[m_SceneNr][i]->GetTransform().GetPosition().y };
					//float widthA = rigidBody->GetWidth();
					float widthB = m_pRigidBodies[m_SceneNr][i]->GetWidth();
					float heightA = rigidBody->GetHeight();
					float heightB = m_pRigidBodies[m_SceneNr][i]->GetHeight();

					//check overlap

					//check widths
					bool isOverlapping = false;
					if (posA.x <= posB.x + widthB && posA.x >= posB.x)
					{
						//check heights
						if (posA.y > posB.y + heightB || posB.y > posA.y + heightA)
						{
							continue;
						}
						else
						{
							isOverlapping = true;
							if (m_pRigidBodies[m_SceneNr][i]->GetTrigger())
							{
								m_pRigidBodies[m_SceneNr][i]->AddOverlappingBody(rigidBody.get());
								m_pRigidBodies[m_SceneNr][i]->OnOverlap(rigidBody.get());
							}
							if (rigidBody->GetTrigger())
							{
								rigidBody->AddOverlappingBody(m_pRigidBodies[m_SceneNr][i].get());
								rigidBody->OnOverlap(m_pRigidBodies[m_SceneNr][i].get());
							}
						}
					}
					if (!isOverlapping)
					{
						if (m_pRigidBodies[m_SceneNr][i]->GetTrigger())
						{
							m_pRigidBodies[m_SceneNr][i]->RemoveOverlappingBody(rigidBody.get());
						}
						if (rigidBody->GetTrigger())
						{
							rigidBody->RemoveOverlappingBody(m_pRigidBodies[m_SceneNr][i].get());
						}
					}

				}
			}
		}
	}
}