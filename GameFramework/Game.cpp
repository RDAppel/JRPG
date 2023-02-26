
#include "_PCH.h"

int Game::s_screenWidth = 1600;
int Game::s_screenHeight = 900;
std::string Game::s_windowTitle = "RPG";


Game::Game()
{
	m_pConsoleHandle = GetConsoleWindow();

	m_isAllegroInitialized = al_init();
	m_resourceManager.SetContentPath("..\\JRPG\\Content\\");

	m_pScreenManager = new ScreenManager(*this);
	m_pSpriteBatch = new SpriteBatch;

	srand(time(0));
}

Game::~Game()
{
	delete m_pInputState;
	delete m_pSpriteBatch;
}


void Game::InitializeDisplay()
{
	if (m_requireVSync) al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	if (m_isDisplayResizable) al_set_new_display_flags(ALLEGRO_RESIZABLE);

	m_pDisplay = al_create_display(s_screenWidth, s_screenHeight);
	if (!m_pDisplay)
	{
		std::cout << "Couldn't initialize the Allegro display!\nPress enter to quit.";
		std::cin.get();
	}
	
	m_pDisplayHandle = al_get_win_window_handle(m_pDisplay);
	al_set_window_title(m_pDisplay, s_windowTitle.c_str());
}


int Game::Run()
{
	m_isRunning = true;

	if (!m_isAllegroInitialized) {
		std::cout << "Couldn't initialize Allegro!\nPress enter to quit.";
		std::cin.get();
	}

	if (!m_isDisplayInitialized) InitializeDisplay();

	al_init_primitives_addon();

	m_pFrameCounterFont = m_resourceManager.Load<Font>("Fonts\\Iceland.ttf");

	m_pInputState = new InputState();
	
	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* pEventQueue = al_create_event_queue();
	ALLEGRO_TIMER* pTimer = al_create_timer(1 / m_targetFramesPerSecond);

	al_start_timer(pTimer);

	al_register_event_source(pEventQueue, al_get_timer_event_source(pTimer));
	al_register_event_source(pEventQueue, al_get_display_event_source(m_pDisplay));
	al_register_event_source(pEventQueue, al_get_keyboard_event_source());
	al_register_event_source(pEventQueue, al_get_mouse_event_source());

	LoadContent(m_resourceManager);

	// need this?
	al_init_image_addon();

	bool redraw = false;

	while (m_isRunning)
	{
		al_wait_for_event(pEventQueue, &event);

		HandleEvent(event);
		
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) Quit();
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP)
		{
			uint8_t mask =
				ALLEGRO_KEYMOD_CTRL | ALLEGRO_KEYMOD_ALT | ALLEGRO_KEYMOD_SHIFT;
			uint8_t modifiers = event.keyboard.modifiers & mask;
			m_pInputState->UpdateModifiers(modifiers);
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT)
		{
			m_gameTime.m_currentTotalTime = al_get_time();
			al_clear_keyboard_state(m_pDisplay);
		}
		else if (event.type == ALLEGRO_EVENT_TIMER)
		{
			Update(m_gameTime);
			redraw = true;
		}

		if (redraw && al_event_queue_is_empty(pEventQueue))
		{
			redraw = false;
			Draw(*m_pSpriteBatch);

			m_frameCounter++;
		}
	}

	al_destroy_timer(pTimer);
	al_destroy_event_queue(pEventQueue);
	al_destroy_display(m_pDisplay);

	return 0;
}


void Game::Update(const GameTime& gameTime)
{
	m_gameTime.Update();
	m_pInputState->Update(m_gameTime);
	m_pScreenManager->HandleInput(*m_pInputState);
	m_pScreenManager->Update(m_gameTime);

	if (!m_displayFrameRate) return;

	m_currentTime = al_get_time();

	double frameTime = m_currentTime - m_previousTime;
	if (frameTime >= 1.0)
	{
		m_actualFramesPerSecond = m_frameCounter / frameTime;
		m_frameCounter = 0;
		m_previousTime = m_currentTime;
	}

	// give the game 2 seconds to stabilize
	if (m_currentTime < 2)
	{
		m_actualFramesPerSecond = m_targetFramesPerSecond;
	}
}

void Game::Draw(SpriteBatch& spriteBatch)
{
	m_pScreenManager->Draw(spriteBatch);

	if (m_displayFrameRate) DisplayFrameRate();

	al_flip_display();
	al_clear_to_color(m_clearColor.GetAllegroColor());
}


void Game::DisplayFrameRate()
{
	double fps = m_actualFramesPerSecond;
	if (!m_pFrameCounterFont)
	{
		std::cout << "FPS: " << fps << "\n";
	}
	else
	{
		ALLEGRO_FONT* pFont = m_pFrameCounterFont->GetAllegroFont();
		const char* format = "%.1f";
		al_draw_textf(pFont, al_map_rgb(0, 0, 0), 9, 9, 0, format, fps);
		al_draw_textf(pFont, al_map_rgb(0, 0, 0), 9, 11, 0, format, fps);
		al_draw_textf(pFont, al_map_rgb(0, 0, 0), 11, 11, 0, format, fps);
		al_draw_textf(pFont, al_map_rgb(0, 0, 0), 11, 9, 0, format, fps);
		al_draw_textf(pFont, al_map_rgb(0, 255, 0), 10, 10, 0, format, fps);
	}

}


bool Game::GetConsoleInput(std::string& text)
{
	if (!m_pConsoleHandle || !m_pDisplayHandle) return false;

	SetForegroundWindow(m_pConsoleHandle);
	std::getline(std::cin, text);
	SetForegroundWindow(m_pDisplayHandle);

	return true;
}