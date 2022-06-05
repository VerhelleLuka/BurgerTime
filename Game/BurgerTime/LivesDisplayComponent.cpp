#include "MiniginPCH.h"
#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "Subject.h"
#include "GameManager.h"
void dae::LivesDisplayComponent::OnNotify(EventType event_, std::shared_ptr<EventArgs> /*args*/)
{
	if (event_ == EventType::LOSTLIFE)
	{
		m_Lives--;
		m_pParent->GetComponent<TextComponent>("TextComponent")->SetText("Lives: " + std::to_string(GameManager::GetInstance().GetLives()));
	}

}