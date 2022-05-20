#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Structs.h"
#include "Observer.h"
#include <functional>
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
		RigidBodyComponent() = default;
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

		//template <typename T>
		//void SetOnOverlapEvent(void (*function)(RigidBodyComponent*), T* functionObj)
		//{
		//	m_OverlapEvent = std::bind(function, functionObj, std::placeholders::_1);
		//}
		void SetOnOverlapEvent(const std::function<void(RigidBodyComponent*)>& function)
		{
			m_OverlapEvent = function;
		}
		void SetOnTriggerExit(const std::function<void(RigidBodyComponent*)>& function)
		{
			m_OnTriggerExit = function;
		}
		void OnOverlap(RigidBodyComponent* other);
		void OnTriggerExit(RigidBodyComponent* other);
		Float2 GetOffset() const { return m_PositionOffset; }
		void SetOffset(Float2 offset) { m_PositionOffset = offset; }

		void Reverse(float elapsedSec);

		void AddOverlappingBody(std::shared_ptr<RigidBodyComponent> overlappingBody);
		void RemoveOverlappingBody(std::shared_ptr<RigidBodyComponent> overlappingBody);
	protected:
		GameObject* m_pParent{};
		//This transform is a reference to the parent transform
		Transform* m_pTransform;

		//m_Direction is for non physics-related movement
		Float2 m_Direction;
		Float2 m_LastDirection;

		//For triggerbox
		float m_Width, m_Height;
			//Position offset
		Float2 m_PositionOffset;
		bool m_IsTrigger;

		//Function pointers
		std::function<void(RigidBodyComponent*)> m_OverlapEvent;
		std::function<void(RigidBodyComponent*)> m_OnTriggerExit;
		std::vector<RigidBodyComponent*> m_OverlappingBodies;
	};
}