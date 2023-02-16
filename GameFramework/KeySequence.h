
#pragma once

#include "_PCH.h"

typedef std::function<void()> OnKeySequenceComplete;

class KeySequence
{

private:

	std::vector<Key> m_keys;

	double m_timeToComplete = 0.0;
	double m_timeElapsed = 0.0;

	double m_timePerKey = 0.0;
	double m_timeElapsedPerKey = 0.0;

	int m_step = 0;

	OnKeySequenceComplete m_onComplete = nullptr;

public:

	KeySequence() {}

	void SetKeys(std::vector<Key> keys) { m_keys = keys; }
	void SetTimeToComplete(double msToComplete) { m_timeToComplete = msToComplete * 0.001; }
	void SetTimePerKey(double msPerKey) { m_timePerKey = msPerKey * 0.001; }
	void SetOnComplete(OnKeySequenceComplete onComplete) { m_onComplete = onComplete; }

	void HandleInput(const InputState& input)
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

	void Update(const GameTime& gameTime)
	{
		//std::cout << m_step << "\n";

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
};
