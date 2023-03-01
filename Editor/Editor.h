#pragma once

#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"

#include "../GameFramework/_PCH.h"

class Editor : public Game
{

private:

	bool m_isDemoVisible = false;

	Texture* m_pTexture = nullptr;

public:

	Editor();
	virtual ~Editor();

	virtual void Update() override;

	virtual void Draw(SpriteBatch& pSpriteBatch) override {}

	virtual void Resize() override;

	virtual void InitializeDisplay() override;

	virtual void HandleEvent(ALLEGRO_EVENT& event) override;

	virtual void LoadContent(ResourceManager& resourceManager) override;
};

