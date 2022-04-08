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
}