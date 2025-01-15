#pragma once
#include <memory>

class GameObject;

class Component
{
public:
	Component()
	{
		m_attachedGameObject = 0;
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
	virtual void Update();
	
	GameObject* GetAttachedGameObject() { return m_attachedGameObject; }

	void SetGameObject(GameObject* go)  {   m_attachedGameObject = go;  }
public:
	bool m_enabled;
	GameObject* m_attachedGameObject;
	bool m_useTick;
	int m_tick_frame_count;
protected:
	int m_tick_counter;
};

