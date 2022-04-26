#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"
void dae::Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::Subject::Notify(EventType event_, std::shared_ptr<EventArgs> args)
{
	for (size_t i{}; i < m_pObservers.size(); ++i)
	{
		m_pObservers[i]->OnNotify(event_, args);
	}
}
