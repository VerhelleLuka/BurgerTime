#pragma once
#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "Observer.h"
#include "RigidBodyComponent.h"
#include "BurgerTime.h"
namespace dae
{
	struct ButtonEventArgs : EventArgs
	{
		std::string name;

	};
	//Had to do this because otherwise in the cpp i get an error for not referencing args
	class ButtonComponent final : public BaseComponent, public Observer
	{
	public:
		virtual void Update(float /*deltaTime*/) override {};
		virtual void FixedUpdate(float /*deltaTime*/) override {}
		virtual void Render() const override {};
		ButtonComponent(const std::string& sceneName, GameMode gameMode): m_SceneName(sceneName), m_GameMode(gameMode), m_OverlappingPeter(false) {};
		virtual ~ButtonComponent() {};
		virtual void OnNotify(EventType event_, std::shared_ptr<EventArgs> args) override;

		void SetOverlapping(bool overlapping) { m_OverlappingPeter = overlapping; }
		//bool GetOverlapping() const { return m_OverlappingPeter; }
	private:
		std::string m_SceneName;
		GameMode m_GameMode;
		bool m_OverlappingPeter;
	};
}
