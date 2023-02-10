#pragma once

#include "_PCH.h"

class InputState
{

	friend class Game;

private:

	ALLEGRO_KEYBOARD_STATE m_currentKeyboardState = ALLEGRO_KEYBOARD_STATE{};
	ALLEGRO_KEYBOARD_STATE m_previousKeyboardState = ALLEGRO_KEYBOARD_STATE{};

	void Update()
	{
		if (al_is_keyboard_installed())
		{
			m_previousKeyboardState = m_currentKeyboardState;
			al_get_keyboard_state(&m_currentKeyboardState);
		}
	}

public:

	InputState()
	{
		al_install_keyboard();
	}


	bool IsKeyDown(Key key)
	{
		return al_key_down(&m_currentKeyboardState, (int)key);
	}

	bool IsKeyUp(Key key)
	{
		return !IsKeyDown(key);
	}

	bool WasKeyDown(Key key)
	{
		return al_key_down(&m_previousKeyboardState, (int)key);
	}

	bool WasKeyUp(Key key)
	{
		return !WasKeyDown(key);
	}


	bool IsNewKeyPress(Key key)
	{
		return IsKeyDown(key) && WasKeyUp(key);
	}

	bool IsNewKeyRelease(Key key)
	{
		return IsKeyUp(key) && WasKeyDown(key);
	}
};