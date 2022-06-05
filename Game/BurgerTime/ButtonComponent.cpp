#include "ButtonComponent.h"
#include "SceneManager.h"
#include "TextComponent.h"
void dae::ButtonComponent::OnNotify(EventType event_, std::shared_ptr<EventArgs> args)
{
	if (event_ == EventType::LOADLEVEL)
	{
		bool incrementLevelIndex = std::static_pointer_cast<ButtonEventArgs>(args)->newLevelIndex;
		if (m_OverlappingPeter)
		{
			GameManager::GetInstance().SetGameMode(m_GameMode);
			GameManager::GetInstance().LoadLevel( incrementLevelIndex);
			SceneManager::GetInstance().SetActiveSceneByName(m_SceneName);
		}
	}
}