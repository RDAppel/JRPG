#include "_PCH.h"


void Screen::Update(const GameTime* pGameTime)
{
	if (m_isExiting)
	{
		if (m_onExitCallback != nullptr)
		{
			m_onExitCallback();
		}

		m_shouldBeRemoved = true;
	}
}