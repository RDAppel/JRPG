
#include "_PCH.h"

bool Texture::s_isAddonInitialized = false;


Texture::Texture()
{
	if (!s_isAddonInitialized)
	{
		s_isAddonInitialized = al_init_image_addon();
	}
}

Texture::~Texture()
{
	al_destroy_bitmap(m_pBitmap);
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