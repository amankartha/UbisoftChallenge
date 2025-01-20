#pragma once
#include "Component.h"
#include "ObserverPattern.h"

class CGameManager;
enum class PlayerState;
class InputHandler;
class Crigidbody;


class CGolfBall :
    public Component , Events::IObserver , Events::ISubject
{
public:
	 CGolfBall(GameObject* attachedObject,int OwnerIndex,int ownerID);
	 ~CGolfBall() override;
	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;
	 void OnNotify(Events::EventType event) override;
	 Crigidbody* GetRigidBody();
	 InputHandler* GetInputHandler();
	 PlayerState* GetPlayerState();
	 void RegisterGameManagerObserver(CGameManager* observer);
		 void RemoveGameManagerObserver(CGameManager* observer);
private:
	void DrawArrow();
 private:
	int m_owner_index_;
	int m_owner_id;
	PlayerState* m_state; 
	InputHandler* m_handler_;
	Crigidbody* m_crigidbody_;
};

