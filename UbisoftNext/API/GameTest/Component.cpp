#include "stdafx.h"
#include "Component.h"

void Component::Update(float DeltaTime)
{
	if (m_useTick)  // only run ever n number of frames
	{
		if (m_tick_counter %= m_tick_frame_count != 0)
		{
			m_tick_counter++;
			return;
		}
		m_tick_counter++;
	}
}
