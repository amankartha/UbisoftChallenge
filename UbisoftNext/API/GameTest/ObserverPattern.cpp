#include "stdafx.h"
#include "ObserverPattern.h"

#include "appUtility.h"

//Note this can register the same observer multiple times incase you want to call a function multiple times
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

void Events::IPatternSubject::RegisterObserver(IPatternObserver& observer)
{
    m_observers_.push_back(&observer);
}

void Events::IPatternSubject::DeRegisterObserver(IPatternObserver& observer)
{
    App::RemoveFromVector(m_observers_, &observer);
}

void Events::IPatternSubject::NotifyObservers(PatternEventType event,IntVector2 gridPosition)
{
    for (auto it = m_observers_.begin(); it != m_observers_.end(); )
    {
        if (*it)
        {
            (*it)->OnNotify(event,gridPosition);
            ++it;
        }
        else
        {
            it = m_observers_.erase(it);
        }
    }
}

void Events::IPhysicsSubject::RegisterPhysicsObserver(IPhysicsObserver& observer)
{
    m_Physics_observers_.push_back(&observer);
}

void Events::IPhysicsSubject::DeRegisterPhysicsObserver(IPhysicsObserver& observer)
{
    App::RemoveFromVector(m_Physics_observers_, &observer);
}

void Events::IPhysicsSubject::NotifyPhysicsObservers(bool isTrigger, int idOne, int idTwo)
{
    if (isTrigger)
    {

        for (auto it = m_Physics_observers_.begin(); it != m_Physics_observers_.end(); )
        {
            if (*it)
            {
                (*it)->OnTriggerEnter(idOne,idTwo);
                ++it;
            }
            else
            {
                it = m_Physics_observers_.erase(it);
            }
        }
    }
    else
    {

        for (auto it = m_Physics_observers_.begin(); it != m_Physics_observers_.end(); )
        {
            if (*it)
            {
                (*it)->OnCollisionEnter(idOne, idTwo);
                ++it;
            }
            else
            {
                it = m_Physics_observers_.erase(it);
            }
        }
    }
}
