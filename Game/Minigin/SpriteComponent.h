#pragma once
#include "GameObject.h"
#include <string>
#include "BaseComponent.h"
namespace dae
{
	class Animation;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent() {};
		~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& rhs) = delete;
		SpriteComponent(SpriteComponent&& rhs) noexcept = delete;

		SpriteComponent& operator=(SpriteComponent&& rhs) noexcept = delete;
		SpriteComponent operator=(const SpriteComponent& rhs) = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() const;

		void SetActiveAnimation(std::shared_ptr<Animation> animation);
		Animation& GetAnimation() const { return *m_pActiveAnimation; }

		void AddAnimation(std::shared_ptr<Animation> animation);

	private:
		//Just one animation per spritecomponent for now
		std::vector<std::shared_ptr<Animation>> m_pAnimation;
		std::shared_ptr<Animation> m_pActiveAnimation;
	};
}

