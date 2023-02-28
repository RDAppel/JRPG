
#pragma once

#include <Windows.h>

#include "../GameFramework/_PCH.h"


class Editor : public Game
{

private:

	HANDLE m_pGameHandle = nullptr;

public:

	Editor();
	virtual ~Editor();

	virtual void Update(const GameTime& gameTime) override;

	virtual void Draw(SpriteBatch& spriteBatch) override;
};

