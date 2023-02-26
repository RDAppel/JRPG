
#pragma once

#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "../GameFramework/_PCH.h"

class Editor : public Game
{

private:


public:

	Editor();
	virtual ~Editor();

	virtual void InitializeDisplay() override;

	virtual void HandleEvent(ALLEGRO_EVENT& event) override;

	virtual void Update(const GameTime& gameTime) override;

	virtual void Draw(SpriteBatch& spriteBatch) override {};
};

