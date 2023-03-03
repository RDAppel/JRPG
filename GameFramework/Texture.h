#pragma once

#include "_PCH.h"


class Texture : public Resource
{

private:

	static bool s_isAddonInitialized;

	ALLEGRO_BITMAP* m_pBitmap = nullptr;

	int m_width = 0;
	int m_height = 0;

public:

	Texture();
	Texture(const Texture&) = delete;
	virtual ~Texture();

	Texture& operator=(const Texture&) = delete;

	virtual bool Load(const std::string& path);

	virtual int GetWidth() const { return m_width; }
	virtual int GetHeight() const { return m_height; }

	virtual Vector2 GetSize() const { return Vector2(m_width, m_height); }

	virtual ALLEGRO_BITMAP* GetAllegroBitmap() const { return m_pBitmap; }

};

