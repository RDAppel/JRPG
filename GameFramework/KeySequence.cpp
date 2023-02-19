
#include "_PCH.h"



void KeySequence::HandleInput(const InputState & input)
{
	if (!m_onComplete) return;

	if (!input.IsAnyNewKeyPressed()) return;
	if (input.IsNewKeyPress(m_keys[m_step]))
	{
		if (m_step == 0) m_timeElapsed = 0.0;
		m_timeElapsedPerKey = 0.0;
		m_step++;
	}
	else m_step = 0;
}

void KeySequence::Update(const GameTime& gameTime)
{
	if (m_step == 0 || !m_onComplete) return;

	m_timeElapsed += gameTime.GetTimeElapsed();
	m_timeElapsedPerKey += gameTime.GetTimeElapsed();

	if (m_timeElapsed > m_timeToComplete && m_timeToComplete > 0) m_step = 0;
	if (m_timeElapsedPerKey > m_timePerKey && m_timePerKey > 0) m_step = 0;

	if (m_step == m_keys.size())
	{
		m_onComplete();
		m_step = 0;
	}
}