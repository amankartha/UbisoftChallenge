#pragma once
#include <memory>

class GameObject;

class Component
{
public:
	Component(GameObject* attachedObject ) :m_attachedGameObject(attachedObject)
	{
		m_tick_frame_count = 0;
		m_enabled = true;
		m_useTick = false;

	};
	virtual ~Component() = default;

	// Move constructor
	Component(Component&& other) noexcept
		: m_enabled(other.m_enabled),
		m_attachedGameObject(other.m_attachedGameObject),
		m_useTick(other.m_useTick),
		m_tick_frame_count(other.m_tick_frame_count),
		m_tick_counter(other.m_tick_counter)
	{
		//// Ensure the moved-from object doesn't retain the original `GameObject*`
		//other.m_attachedGameObject = nullptr;
	}

	virtual void Init() {};
	virtual void Update(float DeltaTime);
	
	GameObject* GetAttachedGameObject() { return m_attachedGameObject; }

	void SetGameObject(GameObject* go)  {   m_attachedGameObject = go;  }
public:
	bool m_enabled;
	GameObject* m_attachedGameObject;  //TODO:: I think this has the chance to become dangled, maybe use ID if errors
	bool m_useTick;
	int m_tick_frame_count;
protected:
	int m_tick_counter;
};

