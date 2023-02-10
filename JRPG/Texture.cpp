#include "Texture.h"

#include <allegro5/allegro_image.h>

bool Texture::s_alAddonInitialized = false;


Texture::Texture()
{
	if (!s_alAddonInitialized)
	{
		s_alAddonInitialized = al_init_image_addon();
	}
}

Texture::~Texture()
{
	delete m_pBitmap;
}

bool Texture::Load(const std::string& path)
{
	m_pBitmap = al_load_bitmap(path.c_str());
	if (m_pBitmap)
	{
		m_width = al_get_bitmap_width(m_pBitmap);
		m_height = al_get_bitmap_height(m_pBitmap);
		return true;
	}

	return false;
}