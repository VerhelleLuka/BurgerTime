#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Structs.h"

namespace dae
{
	class RigidBodyComponent final : public BaseComponent, public Subject
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void Render() const {};

		virtual void SetGameObject(GameObject* go) { m_pParent = go; };
		RigidBodyComponent() :m_pTransform(&m_pParent->GetTransform()) {};
		virtual ~RigidBodyComponent() { m_pTransform = nullptr; delete m_pTransform; };

		void SetDirection(Float2 velocity);
	protected:
		GameObject* m_pParent{};
		//This transform is a reference to the parent transform
		Transform* m_pTransform;
		Float2 m_Direction;
	};
}