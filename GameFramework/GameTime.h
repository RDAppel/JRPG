
#pragma once

class GameTime
{
	friend class Game;

private:

	double m_currentTotalTime = 0;
	double m_previousTotalTime = 0;
	double m_elapsedTime = 0;

	void Update();

public:

	double GetTotalTime() const { return m_currentTotalTime; }
	double GetTimeElapsed() const { return m_elapsedTime; }

};

