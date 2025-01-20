#pragma once
#include <vector>

#include "CustomMath.h"

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
		Transform,
		BallHit
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

	enum class PatternEventType
	{
		base = 0,
		Speed,
		Bomb
	};

	class IPatternObserver
	{
	public:
		virtual ~IPatternObserver() = default;
		virtual void OnNotify(PatternEventType event,IntVector2 gridPosition) = 0;

	};

	class IPatternSubject
	{
	public:
		virtual ~IPatternSubject() = default;
		void RegisterObserver(IPatternObserver& observer);
		void DeRegisterObserver(IPatternObserver& observer);
		void NotifyObservers(PatternEventType event,IntVector2 gridPosition);
	private:
	public:
		std::vector<IPatternObserver*> m_observers_;
	};



	class IPhysicsObserver 
	{
	public:
		virtual ~IPhysicsObserver() = default;
		virtual void OnTriggerEnter(int idOne, int idTwo) = 0;
		virtual void OnCollisionEnter(int idOne, int idTwo) = 0;
	};

	class IPhysicsSubject 
	{
	public:
		virtual ~IPhysicsSubject() = default;

		
		virtual void RegisterPhysicsObserver(IPhysicsObserver& observer) ;

	
		virtual void DeRegisterPhysicsObserver(IPhysicsObserver& observer) ;

		
		virtual void NotifyPhysicsObservers(bool isTrigger, int idOne, int idTwo) ;

	public:
		std::vector<IPhysicsObserver*> m_Physics_observers_;
	};

	
}


