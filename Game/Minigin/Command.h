#pragma once
#include <iostream>
#include "GameObject.h"
#include "PeterPepper.h"
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
			m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetPositions(Float2(250, 0.f));
			m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimation().SetReversed(true);
			if (m_pGameObject->GetComponent<SpriteComponent>("Sprite")->GetAnimationName() != "Run")
				m_pGameObject->GetComponent<SpriteComponent>("Sprite")->SetActiveAnimation("Run");

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
=======
>>>>>>> parent of 29938e7 (Added animations/sprites)
}