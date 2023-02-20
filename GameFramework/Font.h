
#pragma once

#include "_PCH.h"

class Font : public Resource
{

private:

	static bool s_isAddonInitialized;

	ALLEGRO_FONT* m_pFont = nullptr;

public:

	Font();
	Font(const Font&) = delete;
	virtual ~Font();

	Font& operator=(const Font&) = delete;

	virtual bool Load(const std::string& path);

	virtual ALLEGRO_FONT* GetAllegroFont() const { return m_pFont; }
};

