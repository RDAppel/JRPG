
#include "_PCH.h"

void InputState::Update()
{
	if (al_is_keyboard_installed())
	{
		m_previousKeyboardState = m_currentKeyboardState;
		al_get_keyboard_state(&m_currentKeyboardState);

		m_anyNewPressedKeys = false;
		m_anyNewReleasedKeys = false;
		for (uint8_t i = 1; i < (uint8_t)Key::MAX; ++i)
		{
			bool pressed = IsNewKeyPress((Key)i);
			m_anyNewPressedKeys |= pressed;
			m_pressedKeys[i] = pressed;

			bool released = IsNewKeyRelease((Key)i);
			m_anyNewReleasedKeys |= released;
			m_releasedKeys[i] = released;
		}
	}
}


bool InputState::IsKeyDown(Key key) const
{
	return al_key_down(&m_currentKeyboardState, (int)key);
}

bool InputState::IsKeyUp(Key key) const
{
	return !IsKeyDown(key);
}

bool InputState::WasKeyDown(Key key) const
{
	return al_key_down(&m_previousKeyboardState, (int)key);
}

bool InputState::WasKeyUp(Key key) const
{
	return !WasKeyDown(key);
}


bool InputState::IsNewKeyPress(Key key) const
{
	return IsKeyDown(key) && WasKeyUp(key);
}

bool InputState::IsNewKeyRelease(Key key) const
{
	return IsKeyUp(key) && WasKeyDown(key);
}
