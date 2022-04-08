#pragma once
#include "GameObject.h"
#include "EventStructs.h"
namespace dae
{
	struct EventArgs {
		virtual ~EventArgs() = default;
	};
	class Observer
	{
	public:
		friend class Subject;
		virtual ~Observer(){}
		virtual void OnNotify(EventType event_, std::shared_ptr<EventArgs> args) = 0;
	private:
		Observer* m_pNext;
	};
}
