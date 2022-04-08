#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Structs.h"
#include "Renderer.h"
#include "Animation.h"
void dae::SpriteComponent::SetActiveAnimation(const std::string& name)
{
	m_pActiveAnimation.reset();
	m_pActiveAnimation = m_pAnimations[name];

	m_pActiveAnimationName = name;
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

void dae::SpriteComponent::AddAnimation(std::shared_ptr<Animation> animation, const std::string& name)
{
	m_pAnimations[name] = animation;
}

void dae::SpriteComponent::SetPositions(Float2 pos)
{
	for (const std::pair<std::string, std::shared_ptr<Animation>>& element : m_pAnimations) {
		element.second->SetPos(pos);
	}
}