#pragma once
#include <vector>
#include <memory>
#include "CustomMath.h"
class GameObject;




	struct Event
	{
		virtual ~Event() {}
	};

	struct OnPositionChanged : Event
	{
		Vector2 position;
	};

	struct OnMouseOverEvent : Event
	{
		std::weak_ptr<GameObject> GO;
	};

	class IObserver
	{
	public:
		virtual ~IObserver() {}
		virtual void OnNotify(const GameObject& GO, Event& event) = 0;


	};

	class ISubject
	{

	public:
		virtual void addObserver(std::shared_ptr<IObserver> observer)
		{
			m_observers.push_back(observer);
		}
		void removeObserver(std::shared_ptr<IObserver> observer) {
			m_observers.erase(
				std::remove_if(
					m_observers.begin(),
					m_observers.end(),
					[&observer](const std::weak_ptr<IObserver>& weakObs) {
						auto sharedObs = weakObs.lock();
			return sharedObs && sharedObs == observer;
					}
				),
				m_observers.end()
						);
		}

	protected:
		virtual void notify(const GameObject& GO, Event& event)
		{
			for (auto it = m_observers.begin(); it != m_observers.end();)
			{
				if (auto observer = it->lock()) //if exists 
				{
					observer->OnNotify(GO, event);
					++it;
				}
				else
				{
					it = m_observers.erase(it); // remove weakpointers that arent pointing to anything
				}
			}
		}
	private:
		std::vector<std::weak_ptr<IObserver>> m_observers;

	};

