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
	virtual void Init() {};
	virtual void Update();
	
	GameObject* getAttachedGameObject() { return m_attachedGameObject; }

	void SetGameObject(GameObject* go)  {   m_attachedGameObject = go;  }
public:
	bool m_enabled;
	GameObject* m_attachedGameObject;
	bool m_useTick;
	int m_tick_frame_count;
protected:
	int m_tick_counter;
};

