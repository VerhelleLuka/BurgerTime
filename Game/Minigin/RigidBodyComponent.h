#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Structs.h"

namespace dae
{
	class RigidBodyComponent final : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Render() const {};

		virtual void SetGameObject(GameObject* go) { m_pParent = go; };
		RigidBodyComponent() {};
		RigidBodyComponent(float width, float height);
		virtual ~RigidBodyComponent() { m_pTransform = nullptr; delete m_pTransform; };

		void SetDirection(Float2 velocity);
	protected:
		GameObject* m_pParent{};
		//This transform is a reference to the parent transform
		Transform* m_pTransform;

		//m_Direction is for non physics-related movement
		Float2 m_Direction;
		float m_Width, m_Height;

	};
}