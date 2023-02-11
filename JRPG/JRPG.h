#pragma once

class JRPG : public Game
{

private:


public:

	JRPG()
	{
		SetClearColor(Color::REBECCA_PURPLE);

		GetScreenManager()->AddScreen(new ScreenA);
	}

};

