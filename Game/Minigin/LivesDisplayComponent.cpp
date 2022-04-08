#include "MiniginPCH.h"
#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "Subject.h"
void dae::LivesDisplayComponent::OnNotify(EventType event_, std::shared_ptr<EventArgs> /*args*/)
{
	if (event_ == EventType::LOSTLIFE)
	{
		//std::shared_ptr<LivesEventArgs> args1 = std::static_pointer_cast<LivesEventArgs>(args);
		m_Lives--;
		m_pParent->GetComponent<TextComponent>("TextComponent")->SetText("Lives: " + std::to_string(m_Lives));
	}

}