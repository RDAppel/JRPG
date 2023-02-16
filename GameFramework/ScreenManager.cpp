
#include "_PCH.h"


void ScreenManager::AddScreen(Screen& screen)
{
	screen.m_pScreenManager = this;

	screen.LoadContent(m_pGame->GetResourceManager());

	m_screensToAdd.push_back(&screen);
}

void ScreenManager::HandleInput(const InputState& input)
{
	Screen* pScreen;

	bool handleInput = true;

	for (m_rit = m_screens.rbegin(); m_rit != m_screens.rend(); ++m_rit)
	{
		pScreen = *m_rit;
		if (pScreen->ShouldBeRemoved()) continue;
		if (!handleInput) break;

		pScreen->HandleInput(input);
		if (!pScreen->ShouldHandleInputBelow()) break;
	}
}

void ScreenManager::Update(const GameTime& gameTime)
{
	Screen* pScreen;

	//if (m_screensToAdd.size())
	{
		m_screens.insert(m_screens.end(), m_screensToAdd.begin(), m_screensToAdd.end());
		m_screensToAdd.clear();
	}

	//if (m_screens.size())
	{
		bool update = true;

		for (m_rit = m_screens.rbegin(); m_rit != m_screens.rend(); ++m_rit)
		{
			pScreen = *m_rit;

			// update transition

			if (pScreen->ShouldBeRemoved())
			{
				m_screensToRemove.push_back(pScreen);
			}
			else if (update)
			{
				pScreen->Update(gameTime);
				update = pScreen->ShouldUpdateBelow();
			}

		}
	}

	//if (m_screensToRemove.size())
	{
		for (m_it = m_screensToRemove.begin(); m_it != m_screensToRemove.end(); ++m_it)
		{
			pScreen = *m_it;

			pScreen->UnloadContent();

			m_screens.erase(std::remove(m_screens.begin(), m_screens.end(), pScreen), m_screens.end());

			if (pScreen->m_onRemove) pScreen->m_onRemove();

			delete pScreen;
		}
	}

	m_screensToRemove.clear();
}

void ScreenManager::Draw(SpriteBatch& spriteBatch)
{
	Screen* pScreen;

	for (m_rit = m_screens.rbegin(); m_rit != m_screens.rend(); ++m_rit)
	{
		pScreen = *m_rit;
		if (pScreen->ShouldBeRemoved()) continue;

		m_screensToDraw.push_back(pScreen);
		if (!pScreen->ShouldDrawBelow()) break;
	}

	for (m_rit = m_screensToDraw.rbegin(); m_rit != m_screensToDraw.rend(); ++m_rit)
	{
		pScreen = *m_rit;
		pScreen->Draw(spriteBatch);
	}

	m_screensToDraw.clear();
}