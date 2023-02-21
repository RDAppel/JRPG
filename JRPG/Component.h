#pragma once

#include "_PCH.h"

class Character;

class Component
{
	friend class Character;

private:

	Character* m_pCharacter = nullptr;

public:

	enum class Type : uint8_t { NONE, MAP, DIALOG, BATTLE };

	virtual Type GetType() const = 0;

	virtual Character* GetCharacter() { return m_pCharacter; }

};

