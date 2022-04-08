#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Structs.h"
#include "Renderer.h"
#include "Animation.h"
void dae::SpriteComponent::SetActiveAnimation(std::shared_ptr<Animation> animation)
{
	m_pActiveAnimation.reset();
	m_pActiveAnimation = animation;
}

void dae::SpriteComponent::Update(float elapsedSec)
{
	if (m_pActiveAnimation != nullptr)
		m_pActiveAnimation->Update(elapsedSec);
}

void dae::SpriteComponent::Render() const
{
	if (m_pActiveAnimation != nullptr)
		m_pActiveAnimation->Render();
}

void dae::SpriteComponent::AddAnimation(std::shared_ptr<Animation> animation)
{
	m_pAnimations.push_back(animation);
}