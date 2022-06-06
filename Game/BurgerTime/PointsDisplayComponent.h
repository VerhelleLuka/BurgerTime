#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "Observer.h"
#include "EventStructs.h"
namespace dae
{
	struct PointsEventArgs : EventArgs
	{
		int points;
	};
	class PointsDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		virtual void Update(float /*deltaTime*/) override {  };
		virtual void FixedUpdate(float /*deltaTime*/) override {}

		virtual void Render() const override {};
		PointsDisplayComponent(std::shared_ptr<GameObject> pParent) :m_Points(), m_pParent(pParent.get()) {};
		virtual ~PointsDisplayComponent() ;
		PointsDisplayComponent(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent(PointsDisplayComponent&& other) = delete;
		PointsDisplayComponent& operator=(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent& operator=(PointsDisplayComponent&& other) = delete;

		virtual void OnNotify(EventType event_, std::shared_ptr<EventArgs> eventArgs) override;

	protected:
		GameObject* m_pParent{};
		int m_Points;
	};
}

