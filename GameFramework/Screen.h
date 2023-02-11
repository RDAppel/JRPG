
#pragma once

#include "_PCH.h"

class Screen
{
	friend class ScreenManager;

private:

	ScreenManager* m_pScreenManager = nullptr;

public:

	virtual void LoadContent(ResourceManager* pResourceManager);

	virtual void UnloadContent();

	virtual void HandleInput(const InputState* pInput) { }

	virtual void Update(const GameTime* pGameTime) { }

	virtual void Draw(SpriteBatch* pSpriteBatch) = 0;

	virtual bool ShouldHandleInputBelow() { return false; }

	virtual bool ShouldUpdateBelow() { return false; }

	virtual bool ShouldDrawBelow() { return false; }

	virtual bool ShouldBeRemoved() { return false; }

	virtual ScreenManager* GetScreenManager() { return m_pScreenManager; }

};

