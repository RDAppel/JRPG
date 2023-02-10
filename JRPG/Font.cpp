
#include "_PCH.h"

bool Font::s_isAddonInitialized = false;

Font::Font()
{
	if (!s_isAddonInitialized)
	{
		al_init_font_addon();
		al_init_ttf_addon();
		s_isAddonInitialized = true;
	}
}

Font::~Font()
{
	al_destroy_font(m_pFont);
}

bool Font::Load(const std::string& path)
{
	m_pFont = al_load_ttf_font(path.c_str(), 30, 0);
	return m_pFont;
}