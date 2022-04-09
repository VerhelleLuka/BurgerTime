#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Structs.h"
#include "Renderer.h"
#include "Animation.h"
void dae::SpriteComponent::SetActiveAnimation(const std::string& name)
{
	m_pActiveAnimation.reset();
	m_pActiveAnimation = m_pAnimations[name];
	if (name == "Descend")
	{
		std::cout << "Ow yeah\n";
	}
	m_pActiveAnimationName = name;

	//Update all animation positions to prevent weird teleporting
	for (auto& element : m_pAnimations)
	{
		element.second->Update(0.f, m_pParent->GetTransform());
	}

}


void dae::SpriteComponent::Update(float elapsedSec)
{
	if (m_pActiveAnimation != nullptr)
		m_pActiveAnimation->Update(elapsedSec, m_pParent->GetTransform());
}

void dae::SpriteComponent::Render() const
{
	if (m_pActiveAnimation != nullptr)
		m_pActiveAnimation->Render();
}

void dae::SpriteComponent::AddAnimation(std::shared_ptr<Animation> animation,const std::string& name)
{
	m_pAnimations[name] = animation;

}

//void dae::SpriteComponent::SetPositions(Float2 pos)
//{
//	//m_pActiveAnimation->SetPos(pos);
//	//for (auto& element : m_pAnimations)
//	//{
//	//	element.second->SetIsDirty(true);
//	//}
//}