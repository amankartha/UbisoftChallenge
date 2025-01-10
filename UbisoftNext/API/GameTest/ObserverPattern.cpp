#include "stdafx.h"
#include "ObserverPattern.h"

#include "appUtility.h"

void Events::ISubject::RegisterObserver(IObserver& observer)
{
	m_observers_.push_back(&observer);
}

void Events::ISubject::DeRegisterObserver(IObserver& observer)
{
	App::RemoveFromVector(m_observers_, &observer);
}

void Events::ISubject::NotifyObservers(EventType event)
{
    for (auto it = m_observers_.begin(); it != m_observers_.end(); )
    {
        if (*it) 
        {
            (*it)->OnNotify(event); 
            ++it;
        }
        else
        {
            it = m_observers_.erase(it);
        }
    }
}
