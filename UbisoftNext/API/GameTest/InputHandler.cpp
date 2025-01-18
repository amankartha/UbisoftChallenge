#include "stdafx.h"
#include "InputHandler.h"
#include "appUtility.h"

InputHandler::InputHandler(int BufferLength): m_ring_buffer_((std::max)(1,BufferLength))
{}

InputHandler::~InputHandler()
{
}

void InputHandler::SetKeysToTrack(std::vector<int> keys)
{
	assert(keys.size() < 33 && "can only track up to 32 keys") ;

	int i = 0;
	for (auto key : keys)
	{
		m_keyToBit[key] = i++;
	}
}
//Is triggered is key is either held or pressed
bool InputHandler::IsKey(int key)
{
	auto it = m_keyToBit.find(key);
	if (it != m_keyToBit.end())
	{
		return m_currentState[it->second];
	}
	return false;
}

//Is triggered only on the frame that the button is pressed (Not continually)
bool InputHandler::IsKeyPressed(int key)
{
	auto it = m_keyToBit.find(key);
	if (it!=m_keyToBit.end())
	{
		return m_currentState[it->second] && !m_ring_buffer_.Back()[it->second];
	}
	return false; // should go here only if either is not pressed or key doesnt exists
}

bool InputHandler::IsKeyHeld(int key)
{
	auto it = m_keyToBit.find(key);
	if (it != m_keyToBit.end())
	{
		return m_currentState[it->second] && m_ring_buffer_.Front()[it->second];
	}
	return false;
}



//Is triggered the frame that the button is released
bool InputHandler::IsKeyReleased(int key)
{
 	auto it = m_keyToBit.find(key);
	if (it != m_keyToBit.end())
	{
		return !m_currentState[it->second] && m_ring_buffer_.Back()[it->second];
	}
	return false;
}


bool InputHandler::IsKeySequence(std::vector<int> sequence)
{
 //TODO
	return false;
}



void InputHandler::PollInputs()
{
	m_currentState.reset();
	for (auto it = m_keyToBit.begin();it != m_keyToBit.end();it++)
	{
		if ( App::IsKeyPressed(it->first))
		{
			m_currentState.set(it->second);
		}
	}
	if (!m_currentState.none())  // if any key is pressed send out an input event
	{
		NotifyObservers(Events::EventType::Input);
	}
}

void InputHandler::Update()
{
	m_ring_buffer_.Push(m_currentState);
}

std::string InputHandler::GetBufferString() const
{
	return m_ring_buffer_.Back().to_string();
}

std::string InputHandler::GetCurrentString() const
{
	return m_currentState.to_string();
}
