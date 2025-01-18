#pragma once
#include <vector>
#include <memory>
#include "CustomMath.h"
class GameObject;


namespace Events
{
	enum class EventType
	{
		base = 0,
		Input
	};

	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void OnNotify(EventType event) = 0;
	};

	class ISubject
	{
	public:
		virtual ~ISubject() = default;
		void RegisterObserver(IObserver& observer);
		void DeRegisterObserver(IObserver& observer);
		void NotifyObservers(EventType event);
	private:
	public:
		std::vector<IObserver*> m_observers_;
	};
	
}


