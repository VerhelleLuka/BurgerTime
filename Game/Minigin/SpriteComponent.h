#pragma once
#include "GameObject.h"
#include <string>
#include "BaseComponent.h"
#include"Structs.h"
namespace dae
{
	class Animation;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent() {};
		~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& rhs) = delete;
		SpriteComponent(SpriteComponent&& rhs) noexcept;

		SpriteComponent& operator=(SpriteComponent&& rhs) noexcept;
		SpriteComponent operator=(const SpriteComponent& rhs) = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() const;

<<<<<<< HEAD
		void SetActiveAnimation(const std::string& name);
		Animation& GetAnimation() const { return *m_pActiveAnimation; }
		std::string GetAnimationName() const { return m_pActiveAnimationName; }

		void AddAnimation(std::shared_ptr<Animation> animation, const std::string& name);

		void SetPositions(Float2 pos);

	private:
		//Just one animation per spritecomponent for now
		std::map<std::string, std::shared_ptr<Animation>> m_pAnimations;
		std::shared_ptr<Animation> m_pActiveAnimation;
		std::string m_pActiveAnimationName;
=======
		virtual void SetAnimation(std::shared_ptr<Animation> animation);

	private:
		//Just one animation per spritecomponent for now
		std::shared_ptr<Animation> m_pAnimation;
>>>>>>> parent of 29938e7 (Added animations/sprites)
	};
}

