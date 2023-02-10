#pragma once

#include <allegro5/allegro.h>

#include "Resource.h"

class Texture : public Resource
{

private:

	static bool s_alAddonInitialized;

	ALLEGRO_BITMAP* m_pBitmap = nullptr;

	int m_width = 0;
	int m_height = 0;

public:

	Texture();
	virtual ~Texture();

	virtual bool Load(const std::string& path);

	virtual int GetWidth() const { return m_width; }
	virtual int GetHeight() const { return m_height; }

	virtual ALLEGRO_BITMAP* GetAllegroBitmap() { return m_pBitmap; }

};

