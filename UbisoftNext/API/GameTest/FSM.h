#pragma once
#include <memory>

#include "State.h"


namespace AI
{
	class FSM
	{
	public:

		FSM(FSMState* initialState);

		void Update();

		void Transition(FSMState* nextState);


	private:
		FSMState* m_current_state_;
	};


}
