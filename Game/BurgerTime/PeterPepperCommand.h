#pragma once
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
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(50.f, 0.f));
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

				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(-50.f, 0.f));
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
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(0.f, -50.f));
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
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(0.f, 50.f));
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
	class ChangeScene final : public Command
	{
	public:
		void Execute() override
		{
			//if (SceneManager::GetInstance().GetActiveSceneName() == "Level")
			//{
			//	SceneManager::GetInstance().SetActiveSceneByName("MainMenu");
			//}
			//else
			//{
			//	SceneManager::GetInstance().SetActiveSceneByName("Level");
			//}
			//auto sceneObjects = SceneManager::GetInstance().GetActiveScene().GetSceneObjects();
			//for (int i = 0; i < sceneObjects.size(); ++i)
			//{
			//	if (dynamic_cast<GameObject*>(sceneObjects[i].get())->GetComponent<PeterPepperComponent>("PeterPepper").get())
			//	{

			//		InputManager::GetInstance().SetPlayer(dynamic_cast<GameObject*>(sceneObjects[i].get()), 0);
			//	}
			//}

		}
	};
}