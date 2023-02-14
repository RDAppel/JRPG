
#pragma once

#include "_PCH.h"

typedef std::function<void()> OnScreenExitCallback;
typedef std::function<void()> OnScreenRemoveCallback;

class Screen
{
	friend class ScreenManager;

private:

	bool m_isExiting = false;
	bool m_shouldBeRemoved = false;

	ScreenManager* m_pScreenManager = nullptr;

	OnScreenExitCallback m_onExitCallback;
	OnScreenRemoveCallback m_onRemoveCallback;

public:

	virtual void LoadContent(ResourceManager* pResourceManager) {}

	virtual void UnloadContent() {}

	virtual void HandleInput(const InputState* pInput) {}

	virtual void Update(const GameTime* pGameTime);

	virtual void Draw(SpriteBatch* pSpriteBatch) = 0;

	virtual bool ShouldHandleInputBelow() { return false; }

	virtual bool ShouldUpdateBelow() { return false; }

	virtual bool ShouldDrawBelow() { return false; }

	virtual bool ShouldBeRemoved() { return m_shouldBeRemoved; }

	virtual ScreenManager* GetScreenManager() { return m_pScreenManager; }

	virtual void SetOnExitCallback(OnScreenExitCallback callback) { m_onExitCallback = callback; }

	virtual void SetOnRemoveCallback(OnScreenRemoveCallback callback) { m_onRemoveCallback = callback; }

	virtual void Exit() { m_isExiting = true; }

};

