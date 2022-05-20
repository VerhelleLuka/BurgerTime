#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "RigidBodyComponent.h"
#include "PlatformComponent.h"
#include "PeterPepper.h"
namespace dae
{
	class BurgerComponent final : public BaseComponent
	{
	public:
		virtual void Update(float /*deltaTime*/) override {};
		virtual void FixedUpdate(float /*deltaTime*/)override;
		virtual void Render() const override {};
		void Initialize();
		BurgerComponent();
		virtual ~BurgerComponent()
		{}

		void SetOverlapEvent()
		{
			auto binding = std::bind(&BurgerComponent::OnOverlap, this, std::placeholders::_1);
			m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetOnOverlapEvent(binding);
		}
		void ForceFall();

		void SetPeterPepper(PeterPepperComponent* peterPepper) { m_pPeterPepper = peterPepper; }
		PeterPepperComponent* GetPeterPepper()const { return m_pPeterPepper; }

	protected:
		static const int m_NrParts = 4;
		bool m_WalkedOver[m_NrParts] = { false };
		bool m_Fall;
		float m_xPositions[m_NrParts];
		std::shared_ptr<PlatformComponent> m_pPlatformComp;
		void OnOverlap(RigidBodyComponent* other);
		PeterPepperComponent* m_pPeterPepper;

	};
}

