#pragma once
#include "App/app.h"

class InputHandler
{
public:

	InputHandler(int BufferLength):
		m_bufferLength(BufferLength) {}



	bool isKeyPressed(int key)
	{
		return App::IsKeyPressed(key);
	}



	void Update();
private:
	int m_bufferLength;
};

