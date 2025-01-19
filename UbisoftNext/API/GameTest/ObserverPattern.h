#pragma once
#include <vector>

class GameObject;
namespace physics
{
	struct Collision;
}

namespace Events
{
	enum class EventType
	{
		base = 0,
		Input,
		Pattern,
		Transform
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

	class IPhysicsObserver : public IObserver
	{
		virtual ~IPhysicsObserver() = default;
		virtual void OnTriggerEnter(physics::Collision collision) = 0;
		virtual void OnCollisionEnter(physics::Collision collision) = 0;
	};

	class IPhysicsSubject : public ISubject
	{

		virtual ~IPhysicsSubject() = default;

		
		virtual void RegisterPhysicsObserver(IPhysicsObserver& observer) = 0;

	
		virtual void DeRegisterPhysicsObserver(IPhysicsObserver& observer) = 0;

		
		virtual void NotifyPhysicsObservers(physics::Collision) = 0;
	};

	
}


