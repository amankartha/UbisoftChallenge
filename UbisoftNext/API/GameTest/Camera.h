#pragma once
#include <iostream>
#include <algorithm>
#include "CustomMath.h"
#include <App/AppSettings.h>

#include "Ctransform.h"

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
		m_transform->SetPosition(newPos);
	}
	Vector2 GetPosition() const
	{
		return m_transform->GetWorldPosition();
	}
	float GetAngle() const
	{
		return m_transform->GetAngle();
	}
	//Transform& GetTransform() const
	//{
	//	return *m_transform->GetTransform();
	//}
	
	float GetZoom() const
	{
		return m_zoomFactor;
	}
	void SetTransform(Ctransform& transform)
	{
		m_transform = &transform;
	}
	void SetZoom(float zoom)
	{
		m_zoomFactor = std::clamp(zoom,0.5f,2.0f);
	}

	
private:
	Ctransform* m_transform;  //TODO: ideally this shud just use transform but it gets ugly with heirarchy

	float m_zoomFactor;
	
	
};

