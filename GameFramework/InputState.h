#pragma once

#include "_PCH.h"

class InputState
{

	friend class Game;

private:

	ALLEGRO_KEYBOARD_STATE m_currentKeyboardState = ALLEGRO_KEYBOARD_STATE{};
	ALLEGRO_KEYBOARD_STATE m_previousKeyboardState = ALLEGRO_KEYBOARD_STATE{};

	bool m_anyNewPressedKeys = false;
	bool m_anyNewReleasedKeys = false;

	bool m_pressedKeys[(uint8_t)Key::MAX] = { false };
	bool m_releasedKeys[(uint8_t)Key::MAX] = { false };

	void Update();

public:

	InputState() { al_install_keyboard(); }

	bool IsKeyDown(Key key) const;

	bool IsKeyUp(Key key) const;

	bool WasKeyDown(Key key) const;

	bool WasKeyUp(Key key) const;

	bool IsNewKeyPress(Key key) const;

	bool IsNewKeyRelease(Key key) const;

	bool IsAnyNewKeyPressed() const { return m_anyNewPressedKeys; }

	bool IsAnyNewKeyReleased() const { return m_anyNewReleasedKeys; }
};