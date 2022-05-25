#include "ButtonComponent.h"
#include "SceneManager.h"
void dae::ButtonComponent::OnNotify(EventType event_, std::shared_ptr<EventArgs> /*args*/)
{
	if (event_ == EventType::LOADLEVEL)
	{
		SceneManager::GetInstance().SetActiveSceneByName(m_SceneName);
	}
}