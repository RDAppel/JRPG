#pragma once

#include "_PCH.h"

class InputState
{

	friend class Game;

private:

	ALLEGRO_MOUSE_STATE m_currentMouseState = ALLEGRO_MOUSE_STATE{};
	ALLEGRO_MOUSE_STATE m_previousMouseState = ALLEGRO_MOUSE_STATE{};

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

	Vector2 GetMousePosition() const { return Vector2(m_currentMouseState.x, m_currentMouseState.y); }

	bool IsMouseButtonDown(MouseButton button) const { return m_currentMouseState.buttons & (uint8_t)button; }

	bool IsMouseButtonUp(MouseButton button) const { return !(m_currentMouseState.buttons & (uint8_t)button); }

	bool WasMouseButtonDown(MouseButton button) const { return m_previousMouseState.buttons & (uint8_t)button; }

	bool WasMouseButtonUp(MouseButton button) const { return !(m_previousMouseState.buttons & (uint8_t)button); }

	bool IsNewMouseButtonPress(MouseButton button) const { return IsMouseButtonDown(button) && WasMouseButtonUp(button); }

	bool IsNewMouseButtonRelease(MouseButton button) const { return IsMouseButtonUp(button) && WasMouseButtonDown(button); }
};