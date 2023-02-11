
#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Resource.h"

class Font : public Resource
{

private:

	static bool s_isAddonInitialized;

	ALLEGRO_FONT* m_pFont = nullptr;

public:

	Font();
	virtual ~Font();

	virtual bool Load(const std::string& path);

	virtual ALLEGRO_FONT* GetAllegroFont() const { return m_pFont; }
};

