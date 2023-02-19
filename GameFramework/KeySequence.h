
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
	virtual ~KeySequence() {}

	virtual void SetKeys(std::vector<Key> keys) { m_keys = keys; }
	virtual void SetTimeToComplete(double msToComplete) { m_timeToComplete = msToComplete * 0.001; }
	virtual void SetTimePerKey(double msPerKey) { m_timePerKey = msPerKey * 0.001; }
	virtual void SetOnComplete(OnKeySequenceComplete onComplete) { m_onComplete = onComplete; }

	virtual void HandleInput(const InputState& input);
	virtual void Update(const GameTime& gameTime);
};
