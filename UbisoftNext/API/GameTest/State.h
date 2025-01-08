#pragma once
#include <algorithm>


namespace AI
{
	class PushDownAutomata;

	class State
	{
	public:
		virtual void Enter() = 0;
		virtual void Update() = 0;
		virtual void Exit() = 0;
	protected:
		State(PushDownAutomata* pda) : m_pda(pda){}

		virtual ~State() = default;
	protected:
		PushDownAutomata* m_pda;
	};

	class IdleState : public State
	{
	public:
		explicit IdleState(PushDownAutomata* pda)
			: State(pda)
		{
		}

		void Enter() override;
		void Update() override;
		void Exit() override;
	};
};


