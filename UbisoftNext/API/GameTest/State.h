#pragma once
#include <algorithm>


namespace AI
{
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

};


