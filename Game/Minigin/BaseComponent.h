#pragma once
#pragma once
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
	class BaseComponent
	{
	public:
		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime) = 0;
		virtual void Render() const = 0;

		virtual void SetGameObject(GameObject* go) { m_pParent = go; };
		BaseComponent() {};
		virtual ~BaseComponent() {};
	protected :
		GameObject* m_pParent{};
	};
}