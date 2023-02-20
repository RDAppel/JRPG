#pragma once

#include "ScreenA.h"

class JRPG : public Game
{

private:


public:

	JRPG()
	{
		SetClearColor(Color::REBECCA_PURPLE);

		GetScreenManager().AddScreen(*(new ScreenA));
	}

};

