#pragma once
#include <iostream>
#include <algorithm>
#include "CustomMath.h"
#include <App/AppSettings.h>
class Camera
{

public:
	Camera( Vector2 position = Vector2(0, 0), float angle = 0.0) {
		m_transform = nullptr;
		m_zoomFactor = 1;
	}

	~Camera()
	{
		
	}
	void SetPosition(Vector2 newPos)
	{
		m_transform->position = newPos;
	}
	Vector2 GetPosition() const
	{
		return m_transform->position;
	}
	float GetAngle() const
	{
		return m_transform->angle;
	}
	Transform& GetTransform() const
	{
		return *m_transform;
	}
	float GetZoom() const
	{
		return m_zoomFactor;
	}
	void SetTransform(Transform* transform)
	{
		m_transform = transform;
	}
	void SetZoom(float zoom)
	{
		m_zoomFactor = std::clamp(zoom,0.5f,2.0f);
	}

	
private:
	Transform* m_transform;

	float m_zoomFactor;
	
	
};

