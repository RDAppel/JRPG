#pragma once

#include "_PCH.h"

class Character;

class Component
{

private:

	Character* m_pCharacter = nullptr;

public:

	enum class Type : uint8_t { MAP, DIALOG, BATTLE };

	virtual Type GetType() const = 0;

	virtual Character* GetCharacter() { return m_pCharacter; }

};

