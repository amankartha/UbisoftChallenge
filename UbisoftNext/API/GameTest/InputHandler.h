#pragma once
#include <bitset>
#include <unordered_map>

#include "App/app.h"
#include "RingBuffer.h"


class InputHandler
{
public:

	InputHandler(int BufferLength = 10) : m_ring_buffer_((std::max)(1,BufferLength)){}

	void SetKeysToTrack(std::vector<int> keys);

	bool IsKeyPressed(int key);

	bool IsKeyHeld(int key);
	   
	bool IsKeyReleased(int key);

	bool IsKeySequence(std::vector<int> sequence);

	void PollInputs();

	void Update();

	std::string GetBufferString() const;
	std::string GetCurrentString() const;
private:
	
	std::unordered_map<int, int> m_keyToBit; 
	RingBuffer<std::bitset<32>> m_ring_buffer_;        // History of input states
	std::bitset<32> m_currentState;                    // Current bitmask state
};






