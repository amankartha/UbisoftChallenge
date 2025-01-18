#pragma once
#include <memory>
#include <stack>
#include <variant>
#include "State.h"

struct CameraContext;

namespace AI
{
	template<typename T>
	class PushDownAutomata
	{
	public:
		PushDownAutomata(T* Context)
		{
			m_context = Context;
		}
		~PushDownAutomata() {}

		template<typename T>
		State<T>* GetCurrentState()
		{
			if (!m_stateStack.empty())
			{
				return m_stateStack.top();
			}
			return nullptr;
		}

		
		void PushState(State<T>* state) 
		{
			m_stateStack.push(state);
			m_stateStack.top()->Enter();
		};
		
		void PopState()
		{
			if (m_stateStack.empty())
			{
				return;
			}
			GetCurrentState<T>()->Exit();
			m_stateStack.pop();
		}
		void UpdateState()
		{
			if (!m_stateStack.empty())
			{
				GetCurrentState<T>()->Update();
			}
		}
		T* GetContext()
		{
			return m_context;
		}
		
	private:
		T* m_context;
	protected:
		std::stack <State<T>*> m_stateStack;
	};


};


