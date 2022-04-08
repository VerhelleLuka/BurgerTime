#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Structs.h"
#include "Renderer.h"
#include "Animation.h"
<<<<<<< HEAD
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
=======
void dae::SpriteComponent::SetActiveAnimation(std::shared_ptr<Animation> animation)
{
	m_pActiveAnimation.reset();
	m_pActiveAnimation = animation;
>>>>>>> parent of 7237c31 (Broke my sprite component)
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

void dae::SpriteComponent::AddAnimation(std::shared_ptr<Animation> animation)
{
<<<<<<< HEAD
	for (const std::pair<std::string, std::shared_ptr<Animation>>& element : m_pAnimations) {
		element.second->SetPos(pos);
	}
=======
	if (m_pAnimation != nullptr)
		m_pAnimation->Render();
>>>>>>> parent of 29938e7 (Added animations/sprites)
=======
	m_pAnimations.push_back(animation);
>>>>>>> parent of 7237c31 (Broke my sprite component)
}