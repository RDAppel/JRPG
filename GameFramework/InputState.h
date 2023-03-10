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

	uint8_t m_currentModifiers = 0;
	uint8_t m_previousModifiers = 0;

	double m_pressedKeyTimes[(uint8_t)Key::MAX] = { 0 };

	void Update(const GameTime& gameTime);

	void UpdateModifiers(uint8_t modifiers);

public:

	InputState();
	InputState(const InputState&) = delete;

	InputState& operator=(const InputState&) = delete;

	bool IsKeyDown(Key key) const;

	bool IsKeyUp(Key key) const;

	bool WasKeyDown(Key key) const;

	bool WasKeyUp(Key key) const;

	bool IsNewKeyPress(Key key) const;

	bool IsNewKeyRelease(Key key) const;

	bool IsAnyNewKeyPressed() const { return m_anyNewPressedKeys; }

	bool IsAnyNewKeyReleased() const { return m_anyNewReleasedKeys; }

	double GetPressedKeySeconds(Key key) const { return m_pressedKeyTimes[(uint8_t)key]; }

	bool IsKeyModifierDown(KeyModifier modifier) const { return m_currentModifiers & (uint8_t)modifier; }
};