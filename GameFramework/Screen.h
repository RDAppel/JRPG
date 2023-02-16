
#pragma once

#include "_PCH.h"

typedef std::function<void()> OnScreenExit;
typedef std::function<void()> OnScreenRemove;

class Screen
{
	friend class ScreenManager;

private:

	bool m_isExiting = false;
	bool m_shouldBeRemoved = false;

	ScreenManager* m_pScreenManager = nullptr;

	OnScreenExit m_onExit;
	OnScreenRemove m_onRemove;

public:

	virtual void LoadContent(ResourceManager& resourceManager) = 0;

	virtual void UnloadContent() {}

	virtual void HandleInput(const InputState& input) {}

	virtual void Update(const GameTime& gameTime);

	virtual void Draw(SpriteBatch& spriteBatch) = 0;

	virtual bool ShouldHandleInputBelow() { return false; }

	virtual bool ShouldUpdateBelow() { return false; }

	virtual bool ShouldDrawBelow() { return false; }

	virtual bool ShouldBeRemoved() { return m_shouldBeRemoved; }

	virtual ScreenManager& GetScreenManager() { return *m_pScreenManager; }

	virtual void SetOnExit(OnScreenExit onExit) { m_onExit = onExit; }

	virtual void SetOnRemove(OnScreenRemove onRemove) { m_onRemove = onRemove; }

	virtual void Exit() { m_isExiting = true; }

};

