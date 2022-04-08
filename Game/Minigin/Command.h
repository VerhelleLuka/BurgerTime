#pragma once
#include <iostream>
#include "GameObject.h"
#include "PeterPepper.h"
#include "SpriteComponent.h"
namespace dae
{

	class Command {
	public:
		virtual ~Command() = default;

		virtual void Execute() = 0;
		virtual void SetGameObject(GameObject* pGo) { m_pGameObject = pGo; }
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
			m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetPositions(Float2(250.f, 0.f));
			if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() != "RunRight")
				m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetActiveAnimation("RunRight");

		}
	};
	class MoveLeft final : public Command
	{
	public:
		void Execute() override
		{
			m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetPositions(Float2(-250.f, 0.f));
			if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() != "RunLeft")
				m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetActiveAnimation("RunLeft");

		}
	};

	class MoveUp final : public Command
	{
	public:
		void Execute() override
		{
			m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetPositions(Float2(0.f, 250.f));
			if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() != "Climb")
				m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetActiveAnimation("Climb");

		}
	};

	class MoveDown final : public Command
	{
	public:
		void Execute() override
		{
			m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetPositions(Float2(0.f, -250.f));
			if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() != "Descend")
				m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetActiveAnimation("Descend");

		}
	};
	class Idle final : public Command
	{
	public:
		void Execute() override
		{
			if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() != "Idle")

			m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetActiveAnimation("Idle");
		}
	};

}