#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
namespace dae
{
	class Scene;
	class PepperComponent final : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) ;
		virtual void FixedUpdate(float /*deltaTime*/) {};
		virtual void Render() const {};

		PepperComponent() {};
		virtual ~PepperComponent() {};

		virtual void Initialize(Scene& /*scene*/) {};
	protected:
	};
}