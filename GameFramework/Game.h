#pragma once

#include "_PCH.h"

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

	Font* m_pFrameCounterFont = nullptr;

	InputState* m_pInputState = nullptr;

	SpriteBatch* m_pSpriteBatch = nullptr;

	ScreenManager *m_pScreenManager = nullptr;

	ResourceManager m_resourceManager;

	GameTime m_gameTime;

	Color m_clearColor = Color::BLACK;

	Texture* m_pTexture = nullptr;

public:

	Game();
	virtual ~Game();

	static void SetWindowTitle(const std::string title) { s_windowTitle = title; }

	virtual void Update(InputState* pInput);

	virtual int Run();

	virtual void DisplayFrameRate();

	virtual void SetTargetFramesPerSecond(const int frames) { m_targetFramesPerSecond = frames; }

	virtual void Draw(SpriteBatch* pSpriteBatch);

	virtual void SetClearColor(Color color) { m_clearColor = color; }

	virtual ResourceManager* GetResourceManager() { return &m_resourceManager; }

	virtual ScreenManager* GetScreenManager() { return m_pScreenManager; }

};