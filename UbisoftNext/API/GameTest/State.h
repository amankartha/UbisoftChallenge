#pragma once
#include <algorithm>

#include "GameObject.h"


namespace AI
{
	class FSM;

	template<typename T>
	class PushDownAutomata;

	template<typename T>
	class State
	{
	public:
		virtual ~State() {}
		virtual void Enter() = 0;
		virtual void Update() = 0;
		virtual void Exit() = 0;
	protected:
		State( PushDownAutomata<T>* pda) : m_pda(pda){}


		virtual PushDownAutomata<T>* GetPDA()
		{
			return m_pda;
		}

		PushDownAutomata<T>* m_pda;
	};

	
	class FSMState
	{
	public:
		virtual ~FSMState() = default;

		void SetFSM(FSM* fsm,GameObject* owner) { m_fsm_ = fsm; }

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void OnUpdate() = 0;

	private:
		FSM* m_fsm_{ nullptr };

	};


};


