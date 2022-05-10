#pragma once
#include <iostream>
#include "GameObject.h"
#include "PeterPepper.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"
namespace dae
{

	class Command {
	public:
		virtual ~Command() = default;

		virtual void Execute() = 0;
		virtual void SetGameObject(GameObject* pGo) { m_pGameObject = pGo; }
		virtual GameObject* GetGameObject() { return m_pGameObject; }
	protected:
		GameObject* m_pGameObject;
	};

	class Damage final : public Command
	{
	public:
		void Execute() override
		{
			m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->ReduceLife();
		}
	};

	class GainPoints final : public Command
	{
	public:
		void Execute() override
		{
			m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->AddPoints(100);
		}
	};

	class MoveRight final : public Command
	{
	public:
		void Execute() override
		{
			if (m_pGameObject->GetComponent<PeterPepperComponent>("PeterPepper")->GetCanWalkRight())
			{
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(100.f, 0.f));
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
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(-100.f, 0.f));
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
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(0.f, -100.f));
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
				m_pGameObject->GetComponent<RigidBodyComponent>("RigidBody")->SetDirection(Float2(0.f, 100.f));
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

}