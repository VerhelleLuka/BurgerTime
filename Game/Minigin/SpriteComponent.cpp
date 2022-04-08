#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Structs.h"
#include "Renderer.h"
#include "Animation.h"
void dae::SpriteComponent::SetAnimation(std::shared_ptr<Animation> animation)
{
	m_pAnimation.reset();
	m_pAnimation = animation;
}

void dae::SpriteComponent::Update(float elapsedSec)
{
	if (m_pAnimation != nullptr)
		m_pAnimation->Update(elapsedSec);
}

void dae::SpriteComponent::Render() const
{
	if (m_pAnimation != nullptr)
		m_pAnimation->Render();
}