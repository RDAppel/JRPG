#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <iostream>

#include "InputState.h"


class Game
{

private:

	static int s_screenWidth;
	static int s_screenHeight;

	bool m_isInitialized = false;
	float m_frameCounter = 0;
	double m_targetFramesPerSecond = 60;
	bool m_isRunning = true;

	double m_currentTime = 0;
	double m_previousTime = 0;
	double m_actualFramesPerSecond = 0;

	bool m_displayFrameRate = true;

	InputState *m_pInputState = nullptr;

public:

	Game();
	virtual ~Game();

	virtual void Update(InputState* pInput);

	virtual int Run();

	virtual void DisplayFrameRate();

	virtual void SetTargetFramesPerSecond(const int frames) { m_targetFramesPerSecond = frames; }


};