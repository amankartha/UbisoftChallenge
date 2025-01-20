#pragma once
#include "Component.h"
#include "ObserverPattern.h"
#include "GameObjectManager.h"


enum class CameraState
{
	FollowGolfBall,
	LerpToGolfBall,
	FreeRoam
};

class CCameraController : public Component, public Events::IObserver
{
public:
	CCameraController(GameObject* gameObject);

	~CCameraController();

	void Init() override;
	void Update(float DeltaTime) override;
	void OnNotify(const Events::EventType event) override;
	void SetTransformToFollow(Ctransform* transform);
private:
	CameraState m_state_;
	Vector2 m_direction;
	Ctransform* m_transformToFollow;
};

inline void CCameraController::SetTransformToFollow(Ctransform* transform)
{
	m_transformToFollow = transform;
}
