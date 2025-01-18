#pragma once
#include "Component.h"
#include "ObserverPattern.h"

class Ccamera;
class Camera;

class CCameraController : public Component, public Events::IObserver
{
public:
	~CCameraController();

	void Init() override;
	void Update() override;
	void OnNotify(const Events::EventType event) override;

private:
	Vector2 m_direction;
	Ccamera* m_camera_;

};
