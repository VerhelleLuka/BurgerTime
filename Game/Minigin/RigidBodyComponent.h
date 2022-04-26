#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Structs.h"
#include "Observer.h"
namespace dae
{
	struct RigdBodyEventArgs : EventArgs
	{
		Transform otherTransform;
	};
	class RigidBodyComponent final : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float deltaTime) override;
		virtual void Render() const {};

		virtual void SetGameObject(GameObject* go) { m_pParent = go; };
		RigidBodyComponent() {};
		RigidBodyComponent(float width, float height, bool isTrigger);
		virtual ~RigidBodyComponent() { m_pTransform = nullptr; delete m_pTransform; };

		void SetDirection(Float2 velocity);

		//All the getters for component overlap
		bool GetTrigger() const { return m_IsTrigger; }
		Transform GetTransform() const { return *m_pTransform; }
		void SetTransform(Transform* transform) { m_pTransform = transform; }
		float GetWidth()const { return m_Width; }
		float GetHeight()const { return m_Height; }
		GameObject* GetParent() const { return m_pParent; }
	protected:
		GameObject* m_pParent{};
		//This transform is a reference to the parent transform
		Transform* m_pTransform;

		//m_Direction is for non physics-related movement
		Float2 m_Direction;

		//For triggerbox
		float m_Width, m_Height;
		bool m_IsTrigger;

	};
}