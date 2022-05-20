#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "RigidBodyComponent.h"
#include "PlatformComponent.h"
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

	protected:
		static const int m_NrParts = 4;
		bool m_WalkedOver[m_NrParts] = { false };
		bool m_Fall;
		float m_xPositions[m_NrParts];
		std::shared_ptr<PlatformComponent> m_pPlatformComp;
		std::shared_ptr<PlatformComponent> m_pPrevPlatformComp;
		void OnOverlap(RigidBodyComponent* other);

	};
}

