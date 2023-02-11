
#pragma once

#include "_PCH.h"

class ScreenManager
{

private:

	Game* m_pGame = nullptr;

	std::vector<Screen*> m_screens;
	std::vector<Screen*> m_screensToAdd;
	std::vector<Screen*> m_screensToRemove;
	std::vector<Screen*> m_screensToDraw;

	std::vector<Screen*>::iterator m_it;
	std::vector<Screen*>::reverse_iterator m_rit;

public: 

	ScreenManager(Game* pGame) { m_pGame = pGame; }
	virtual ~ScreenManager() {}

	virtual void AddScreen(Screen* pScreen);

	virtual void HandleInput(const InputState* pInput);

	virtual void Update(const GameTime* pGameTime);

	virtual void Draw(SpriteBatch* pSpriteBatch);


};

