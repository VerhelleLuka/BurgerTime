//#pragma once
#include "GameObject.h"
#include "Command.h"
#include "PeterPepper.h"
#include "Structs.h"
#include "SceneManager.h"
#include "SceneObject.h"
#include "Scene.h"
#include <string>
namespace dae
{
	class MoveRight final : public Command
	{
	public:
		void Execute() override
		{
			if (m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->GetCanWalkRight())
			{
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(75.f, 0.f));
				m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->ChangeState(2);

			}
		}
	};
	class MoveLeft final : public Command
	{
	public:
		void Execute() override
		{
			if (m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->GetCanWalkLeft())
			{

				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(-75.f, 0.f));
				m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->ChangeState(1);
			}
		}
	};

	class MoveUp final : public Command
	{
	public:
		void Execute() override
		{
			if (m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->GetCanClimb())
			{
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(0.f, -75.f));
				m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->ChangeState(3);
			}
		}
	};
	class MoveDown final : public Command
	{
	public:
		void Execute() override
		{
			if (m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->GetCanDescend())
			{
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(0.f, 75.f));
				m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->ChangeState(4);
			}
		}
	};
	class Idle final : public Command
	{
	public:
		void Execute() override
		{
			m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->ChangeState(0);
		}
	};
	class Select final : public Command
	{
	public:
		void Execute() override
		{
			m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->ButtonPress();
			auto sceneObjects = SceneManager::GetInstance().GetActiveScene().GetSceneObjects();
			for (int i = 0; i < sceneObjects.size(); ++i)
			{
				if (dynamic_cast<GameObject*>(sceneObjects[i].get())->GetComponent<PeterPepperComponent>("PeterPepper").get())
				{

					InputManager::GetInstance().SetPlayer(dynamic_cast<GameObject*>(sceneObjects[i].get()), 0);
				}
			}
		}
	};
	class Pepper final : public Command
	{
	public:
		void Execute() override
		{
			float animationScale = 1.75f;

			auto pepperGo = std::make_shared<GameObject>();

			auto pepperAnimation = std::make_shared<Animation>(4, 4);
			pepperAnimation->SetTexture("PeterPepper/Pepper.png");
			pepperAnimation->SetScale(animationScale);

			auto pepperSprite = std::make_shared<SpriteComponent>();
			pepperGo->AddComponent(pepperSprite, "Sprite");
			pepperSprite->AddAnimation(pepperAnimation, "Pepper");
			pepperSprite->SetActiveAnimation("Pepper");

			auto pRigidBody = std::make_shared<RigidBodyComponent>(pepperSprite->GetAnimation().GetScaledWidth(),
				pepperSprite->GetAnimation().GetScaledHeight(),
				true);

			pepperGo->AddComponent(pRigidBody, "Pepper");

			if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() == "Runright")
			{
				pepperGo->SetTransform(m_pGameObject->GetTransform().GetPosition().x + pepperAnimation->GetScaledWidth(), m_pGameObject->GetTransform().GetPosition().y, 0.f);

			}
			else if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() == "RunLeft")
			{
				pepperGo->SetTransform(m_pGameObject->GetTransform().GetPosition().x - pepperAnimation->GetScaledWidth(), m_pGameObject->GetTransform().GetPosition().y, 0.f);

			}
			else if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() == "Climb")
			{
				pepperGo->SetTransform(m_pGameObject->GetTransform().GetPosition().x, m_pGameObject->GetTransform().GetPosition().y - pepperAnimation->GetScaledHeight(), 0.f);

			}
			else if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() == "Descend")
			{
				pepperGo->SetTransform(m_pGameObject->GetTransform().GetPosition().x, m_pGameObject->GetTransform().GetPosition().y + pepperAnimation->GetScaledHeight(), 0.f);
			}
			else if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() == "Idle")
			{
				pepperGo->SetTransform(m_pGameObject->GetTransform());

			}
			SceneManager::GetInstance().GetActiveScene().Add(pepperGo);
		}
	};
}