#pragma once

#include "_PCH.h"

class Game
{

private:

	static int s_screenWidth;
	static int s_screenHeight;
	static std::string s_windowTitle;

	float m_frameCounter = 0;
	double m_targetFramesPerSecond = 60;
	bool m_isRunning = true;

	bool m_requireVSync = false;

	bool m_isAllegroInitialized = false;
	bool m_isDisplayInitialized = false;
	bool m_isDisplayResizable = false;

	double m_currentTime = 0;
	double m_previousTime = 0;
	double m_actualFramesPerSecond = 0;

	bool m_displayFrameRate = true;

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


protected:

	ALLEGRO_DISPLAY* m_pDisplay = nullptr;

	virtual void SetRequireVSync(const bool require = true) { m_requireVSync = require; }

	virtual void SetScreenSize(const Vector2& size) { s_screenWidth = size.X; s_screenHeight = size.Y; }

	virtual void SetDisplayResizable(const bool resizable = true) { m_isDisplayResizable = resizable; }

	virtual void SetTargetFramesPerSecond(const int frames) { m_targetFramesPerSecond = frames; }

	virtual void InitializeDisplay();


public:

	Game();
	virtual ~Game();

	virtual int Run();

	static void SetWindowTitle(const std::string title) { s_windowTitle = title; }

	static Vector2 GetScreenSize() { return Vector2(s_screenWidth, s_screenHeight); }

	virtual void LoadContent(ResourceManager& resourceManager) {};

	virtual void Update(const GameTime& gameTime);

	virtual void Draw(SpriteBatch& pSpriteBatch);

	virtual void DisplayFrameRate();

	virtual void SetClearColor(Color color) { m_clearColor = color; }

	virtual Color GetClearColor() { return m_clearColor; }

	virtual ResourceManager& GetResourceManager() { return m_resourceManager; }

	virtual ScreenManager& GetScreenManager() { return *m_pScreenManager; }

	virtual bool GetConsoleInput(std::string& text);

	virtual void HandleEvent(ALLEGRO_EVENT& event) {}

	virtual void Quit() { m_isRunning = false; }


};