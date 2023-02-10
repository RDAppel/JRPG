
#include "Game.h"
#include "Texture.h"

int Game::s_screenWidth = 1280;
int Game::s_screenHeight = 768;
std::string Game::s_windowTitle = "RPG";


Game::Game()
{
	m_isInitialized = al_init();
	m_resourceManager.SetContentPath("..\\JRPG\\Content\\");
}

Game::~Game()
{
	delete m_pInputState;
}

void Game::Update(InputState* pInput)
{
}

int Game::Run()
{
	m_isRunning = true;

	if (!m_isInitialized) {
		std::cout << "Couldn't initialize Allegro!";
		return -1;
	}

	ALLEGRO_DISPLAY* pDisplay = al_create_display(s_screenWidth, s_screenHeight);
	if (!pDisplay)
	{
		std::cout << "Couldn't create a display!";
		return -1;
	}

	al_set_window_title(pDisplay, s_windowTitle.c_str());

	ALLEGRO_EVENT_QUEUE* pEventQueue = al_create_event_queue();
	ALLEGRO_TIMER* pTimer = al_create_timer(1 / m_targetFramesPerSecond);


	//bool isImageAddonInitialized = al_init_image_addon();
	//ALLEGRO_BITMAP* pChestImage = al_load_bitmap("..\\JRPG\\Content\\Textures\\Spritesheets\\Chest.png");

	Texture* pTexture = m_resourceManager.Load<Texture>("Textures\\Spritesheets\\Chest.png");

	ALLEGRO_EVENT alEvent;
	al_start_timer(pTimer);

	al_register_event_source(pEventQueue, al_get_timer_event_source(pTimer));
	al_register_event_source(pEventQueue, al_get_display_event_source(pDisplay));

	m_pInputState = new InputState();

	if (al_is_keyboard_installed()) {
		al_register_event_source(pEventQueue, al_get_keyboard_event_source());
	}

	bool redraw = false;

	while (m_isRunning)
	{
		al_wait_for_event(pEventQueue, &alEvent);

		if (alEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			m_isRunning = false;
		}
		else if (alEvent.type == ALLEGRO_EVENT_TIMER)
		{
			m_pInputState->Update();
			Update(m_pInputState);
			redraw = true;
		}

		if (redraw && al_event_queue_is_empty(pEventQueue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 255));

			al_draw_bitmap(pTexture->GetAllegroBitmap(), 32, 32, 0);

			al_flip_display();

			m_frameCounter++;

			if (m_displayFrameRate) DisplayFrameRate();
		}
	}

	return 0;
}

void Game::DisplayFrameRate()
{
	m_currentTime = al_get_time();

	double difference = m_currentTime - m_previousTime;
	if (difference >= 1.0)
	{
		m_actualFramesPerSecond = m_frameCounter / difference;
		m_frameCounter = 0;
		m_previousTime = m_currentTime;
	}

	std::cout << "FPS: " << m_actualFramesPerSecond << "\n";

}