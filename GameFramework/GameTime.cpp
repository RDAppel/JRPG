
#include "_PCH.h"


void GameTime::Update()
{
	m_previousTotalTime = m_currentTotalTime;
	m_currentTotalTime = al_get_time();
	m_elapsedTime = m_currentTotalTime - m_previousTotalTime;
}