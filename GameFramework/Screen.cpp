#include "_PCH.h"


void Screen::Update(const GameTime& gameTime)
{
	if (m_isExiting)
	{
		if (m_onExit != nullptr) m_onExit();
		m_shouldBeRemoved = true;
	}
}