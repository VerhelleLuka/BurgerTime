#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Structs.h"
#include "Renderer.h"
#include "Animation.h"
<<<<<<< HEAD
void dae::SpriteComponent::SetActiveAnimation(const std::string& name)
{
	m_pActiveAnimation.reset();
	m_pActiveAnimation = m_pAnimations[name];

	m_pActiveAnimationName = name;
=======
void dae::SpriteComponent::SetAnimation(std::shared_ptr<Animation> animation)
{
	m_pAnimation.reset();
	m_pAnimation = animation;
>>>>>>> parent of 29938e7 (Added animations/sprites)
}

void dae::SpriteComponent::Update(float elapsedSec)
{
	if (m_pAnimation != nullptr)
		m_pAnimation->Update(elapsedSec);
}

void dae::SpriteComponent::Render() const
{
<<<<<<< HEAD
	if (m_pActiveAnimation != nullptr)
		m_pActiveAnimation->Render();
}

void dae::SpriteComponent::AddAnimation(std::shared_ptr<Animation> animation, const std::string& name)
{
	m_pAnimations[name] = animation;
}

void dae::SpriteComponent::SetPositions(Float2 pos)
{
	for (const std::pair<std::string, std::shared_ptr<Animation>>& element : m_pAnimations) {
		element.second->SetPos(pos);
	}
=======
	if (m_pAnimation != nullptr)
		m_pAnimation->Render();
>>>>>>> parent of 29938e7 (Added animations/sprites)
}