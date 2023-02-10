#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <iostream>

#include "InputState.h"
#include "ResourceManager.h"


class Game
{

private:

	static int s_screenWidth;
	static int s_screenHeight;
	static std::string s_windowTitle;

	bool m_isInitialized = false;
	float m_frameCounter = 0;
	double m_targetFramesPerSecond = 60;
	bool m_isRunning = true;

	double m_currentTime = 0;
	double m_previousTime = 0;
	double m_actualFramesPerSecond = 0;

	bool m_displayFrameRate = true;

	InputState *m_pInputState = nullptr;

	ResourceManager m_resourceManager;

public:

	Game();
	virtual ~Game();

	static void SetWindowTitle(const std::string title) { s_windowTitle = title; }

	virtual void Update(InputState* pInput);

	virtual int Run();

	virtual void DisplayFrameRate();

	virtual void SetTargetFramesPerSecond(const int frames) { m_targetFramesPerSecond = frames; }

};