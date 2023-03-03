
#pragma once

#include <Windows.h>

#include "../RPGLibrary/_PCH.h"

#include "Window.h"

class Editor : public Game
{

private:

	HANDLE m_pGameHandle = nullptr;

	std::unordered_map<std::string, Window*> m_windows;

public:

	Editor();
	virtual ~Editor();

	virtual void LoadContent(ResourceManager& resourceManager) override;

	virtual void Update(const GameTime& gameTime) override;

	virtual void Draw(SpriteBatch& spriteBatch) override;
};

