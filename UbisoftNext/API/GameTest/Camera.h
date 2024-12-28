#pragma once
#include <iostream>
#include "CustomMath.h"
class Camera
{
private: 
	Vector2 m_positon;
public:
	Camera( Vector2 position = Vector2(0, 0)) :m_positon(position) {}

	~Camera()
	{
		
	}
	void SetPosition(Vector2 newPos)
	{
		m_positon = newPos;
	}
	Vector2 GetPosition()
	{
		return m_positon;
	}
};

