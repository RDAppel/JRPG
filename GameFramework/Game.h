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

	bool m_requireVSync = false;

	double m_currentTime = 0;
	double m_previousTime = 0;
	double m_actualFramesPerSecond = 0;

	bool m_displayFrameRate = true;

	ALLEGRO_DISPLAY* m_pDisplay = nullptr;

	Font* m_pFrameCounterFont = nullptr;

	InputState* m_pInputState = nullptr;

	SpriteBatch* m_pSpriteBatch = nullptr;

	ScreenManager* m_pScreenManager = nullptr;

	ResourceManager m_resourceManager;

	GameTime m_gameTime;

	Color m_clearColor = Color::BLACK;

	Texture* m_pTexture = nullptr;

	HWND m_pConsoleHandle = nullptr;
	HWND m_pDisplayHandle = nullptr;

public:

	Game();
	virtual ~Game();

	static void SetWindowTitle(const std::string title) { s_windowTitle = title; }

	static Vector2 GetScreenSize() { return Vector2(s_screenWidth, s_screenHeight); }

	virtual void Update();

	virtual int Run();

	virtual void LoadContent(ResourceManager& resourceManager) {};

	virtual void DisplayFrameRate();

	virtual void SetRequireVSync(const bool require = true) { m_requireVSync = require; }

	virtual void SetTargetFramesPerSecond(const int frames) { m_targetFramesPerSecond = frames; }

	virtual void Draw(SpriteBatch& pSpriteBatch);

	virtual void SetClearColor(Color color) { m_clearColor = color; }

	virtual ResourceManager& GetResourceManager() { return m_resourceManager; }

	virtual ScreenManager& GetScreenManager() { return *m_pScreenManager; }

	virtual bool GetConsoleInput(std::string& text);


};