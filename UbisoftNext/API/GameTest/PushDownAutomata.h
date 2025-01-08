#pragma once
#include <stack>
#include "State.h"

namespace AI
{

	struct Context
	{
		
	};

	class PushDownAutomata
	{
	public:
		PushDownAutomata(Context context) : m_context(context){}

		State* GetCurrentState();
		void PushState(State& state);
		void PopState();
		void UpdateState();
		void SetContext(Context context);
	public:
		Context m_context;
	private:
		std::stack<State*> m_stateStack;
	};
};


