#pragma once

#include "_PCH.h"

class Game
{

private:

	static int s_screenWidth;
	static int s_screenHeight;
	static std::string s_windowTitle;

	bool m_isAllegroInitialized = false;
	bool m_isDisplayInitialized = false;

	float m_frameCounter = 0;
	double m_targetFramesPerSecond = 60;
	bool m_isRunning = true;

	bool m_requireVSync = false;
	bool m_isDisplayResizable = false;

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

protected:

	ALLEGRO_DISPLAY* GetDisplay() { return m_pDisplay; }

public:

	Game();
	virtual ~Game();

	static void SetScreenSize(const int width, const int height) { s_screenWidth = width; s_screenHeight = height; }

	static void SetWindowTitle(const std::string title) { s_windowTitle = title; }

	static Vector2 GetScreenSize() { return Vector2(s_screenWidth, s_screenHeight); }

	virtual void Update();

	virtual void InitializeDisplay();

	virtual int Run();

	virtual void LoadContent(ResourceManager& resourceManager) {};

	virtual void DisplayFrameRate();

	virtual void SetDisplayResizable(const bool resizable = true) { m_isDisplayResizable = resizable; }

	virtual void SetDisplayFrameRate(const bool display = true) { m_displayFrameRate = display; }

	virtual void SetRequireVSync(const bool require = true) { m_requireVSync = require; }

	virtual void SetTargetFramesPerSecond(const int frames) { m_targetFramesPerSecond = frames; }

	virtual void Draw(SpriteBatch& pSpriteBatch);

	virtual void SetClearColor(Color color) { m_clearColor = color; }

	virtual Color& GetClearColor() { return m_clearColor; }

	virtual ResourceManager& GetResourceManager() { return m_resourceManager; }

	virtual ScreenManager& GetScreenManager() { return *m_pScreenManager; }

	virtual bool GetConsoleInput(std::string& text);

	virtual void Resize() { al_acknowledge_resize(m_pDisplay); }

	virtual void HandleEvent(ALLEGRO_EVENT& event) {}

	virtual void Quit() { m_isRunning = false; }

};