#pragma once
#include "Component.h"
#include "ObserverPattern.h"

enum class PlayerState;
class InputHandler;
class Crigidbody;


class CGolfBall :
    public Component , Events::IObserver
{
public:
	 CGolfBall(GameObject* attachedObject,int OwnerIndex);
	 ~CGolfBall();
	void Init() override;
	void Update(float DeltaTime) override;
	void UpdateState(PlayerState state);
	 void OnNotify(Events::EventType event) override;
	 Crigidbody* GetRigidBody();
	 InputHandler* GetInputHandler();
 private:
	int m_owner_index_;
	PlayerState m_state;
	InputHandler* m_handler_;
	Crigidbody* m_crigidbody_;
};

