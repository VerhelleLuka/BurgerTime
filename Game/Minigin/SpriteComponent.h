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
		SpriteComponent(SpriteComponent&& rhs) noexcept;

		SpriteComponent& operator=(SpriteComponent&& rhs) noexcept;
		SpriteComponent operator=(const SpriteComponent& rhs) = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() const;

<<<<<<< HEAD
<<<<<<< HEAD
		void SetActiveAnimation(const std::string& name);
=======
		void SetActiveAnimation(std::shared_ptr<Animation> animation);
>>>>>>> parent of 7237c31 (Broke my sprite component)
		Animation& GetAnimation() const { return *m_pActiveAnimation; }

		void AddAnimation(std::shared_ptr<Animation> animation);

	private:
		//Just one animation per spritecomponent for now
		std::vector<std::shared_ptr<Animation>> m_pAnimation;
		std::shared_ptr<Animation> m_pActiveAnimation;
<<<<<<< HEAD
		std::string m_pActiveAnimationName;
=======
		virtual void SetAnimation(std::shared_ptr<Animation> animation);

	private:
		//Just one animation per spritecomponent for now
		std::shared_ptr<Animation> m_pAnimation;
>>>>>>> parent of 29938e7 (Added animations/sprites)
=======
>>>>>>> parent of 7237c31 (Broke my sprite component)
	};
}

