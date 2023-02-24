
#include "_PCH.h"

SpriteBatch::SpriteBatch(const uint32_t defaultCount)
{
	for (uint32_t i = 0; i < defaultCount; ++i)
	{
		m_inactiveDrawables.push_back(new Drawable());
	}
}

SpriteBatch::~SpriteBatch()
{
	for (auto drawable : m_inactiveDrawables) delete drawable;
}

void SpriteBatch::Begin(const SpriteSortMode sortMode,
	BlendState blendState, const Transform* pTransform)
{
	m_isStarted = true;
	m_sortMode = sortMode;

	m_it = m_inactiveDrawables.begin();

	if (blendState == BlendState::ALPHA)
	{
		al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	}
	else if (blendState == BlendState::ADDITIVE)
	{
		al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
	}

	if (pTransform) pTransform->Apply();
}

void SpriteBatch::End()
{
	if (m_sortMode != SpriteSortMode::IMMEDIATE)
	{
		if (m_sortMode == SpriteSortMode::BACK_TO_FRONT)
		{
			std::sort(m_drawables.begin(), m_drawables.end(), Compare::FrontToBack());
		}
		else if (m_sortMode == SpriteSortMode::FRONT_TO_BACK)
		{
			std::sort(m_drawables.begin(), m_drawables.end(), Compare::BackToFront());
		}

		m_it = m_drawables.begin();
		for (; m_it != m_drawables.end(); ++m_it)
		{
			if ((*m_it)->isBitmap) DrawBitmap(*m_it);
			else DrawFont(*m_it);
		}
	}

	std::cout << "Drawn " << m_drawables.size() << " sprites." << std::endl;

	m_drawables.clear();
	Transform::IDENTITY.Apply();
}

void SpriteBatch::Draw(const Texture* pTexture, const Vector2 position, const Color color,
	const Vector2 origin, const Vector2 scale, const float rotation, const float drawDepth)
{
	Region source(0, 0, pTexture->GetWidth(), pTexture->GetHeight());
	Draw(pTexture, position, source, color, origin, scale, rotation, drawDepth);
}

void SpriteBatch::Draw(const Texture* pTexture, const Vector2 position, const Region& source,
	const Color color, const Vector2 origin, const Vector2 scale, const float rotation, const float drawDepth)
{
	assert(m_isStarted && "You must call Begin() before drawing.");

	Drawable* pDrawable;

	if (m_it != m_inactiveDrawables.end())
	{
		pDrawable = *m_it;
		m_it++;
	}
	else
	{
		pDrawable = new Drawable();
		m_inactiveDrawables.push_back(pDrawable);
		m_it = m_inactiveDrawables.end();
	}

	pDrawable->isBitmap = true;
	pDrawable->Type.pBitmap = pTexture->GetAllegroBitmap();
	pDrawable->x = position.X;
	pDrawable->y = position.Y;
	pDrawable->color = color.GetAllegroColor();
	pDrawable->Type.sx = source.X;
	pDrawable->Type.sy = source.Y;
	pDrawable->Type.sw = source.Width;
	pDrawable->Type.sh = source.Height;
	pDrawable->Type.cx = origin.X;
	pDrawable->Type.cy = origin.Y;
	pDrawable->Type.scx = scale.X;
	pDrawable->Type.scy = scale.Y;
	pDrawable->Type.rotation = rotation;
	pDrawable->depth = drawDepth;

	if (m_sortMode == SpriteSortMode::IMMEDIATE) DrawBitmap(pDrawable);
	else m_drawables.push_back(pDrawable);
}

void SpriteBatch::Draw(const Animation* pAnimation, const Vector2 position, const Color color, const Vector2 origin, const Vector2 scale, const float rotation, const float drawDepth)
{
	Draw(pAnimation->GetTexture(), position, pAnimation->GetCurrentFrame(), color, origin, scale, rotation, drawDepth);
}


void SpriteBatch::Draw(const Font* pFont, std::string pText, const Vector2 position,
	const Color color, const float drawDepth)
{
	assert(m_isStarted && "You must call Begin() before drawing.");

	Drawable* pDrawable;

	if (m_it != m_inactiveDrawables.end())
	{
		pDrawable = *m_it;
		m_it++;
	}
	else
	{
		pDrawable = new Drawable();
		m_inactiveDrawables.push_back(pDrawable);
		m_it = m_inactiveDrawables.end();
	}

	unsigned int index = (int)m_textCopies.size();
	m_textCopies.push_back(pText);

	pDrawable->isBitmap = false;
	pDrawable->Type.isTextStored = true;
	pDrawable->Type.pFont = pFont->GetAllegroFont();
	pDrawable->Type.TextSource.index = index;
	pDrawable->x = position.X;
	pDrawable->y = position.Y;
	pDrawable->color = color.GetAllegroColor();

	if (m_sortMode == SpriteSortMode::IMMEDIATE) DrawFont(pDrawable);
	else m_drawables.push_back(pDrawable);

}


void SpriteBatch::Draw(const Font* pFont, std::string* pText, const Vector2 position,
	const Color color, const float drawDepth)
{
	assert(m_isStarted && "You must call Begin() before drawing.");

	Drawable* pDrawable;

	if (m_it != m_inactiveDrawables.end())
	{
		pDrawable = *m_it;
		m_it++;
	}
	else
	{
		pDrawable = new Drawable();
		m_inactiveDrawables.push_back(pDrawable);
		m_it = m_inactiveDrawables.end();
	}

	pDrawable->isBitmap = false;
	pDrawable->Type.isTextStored = false;
	pDrawable->Type.pFont = pFont->GetAllegroFont();
	pDrawable->Type.TextSource.pText = pText;
	pDrawable->x = position.X;
	pDrawable->y = position.Y;
	pDrawable->color = color.GetAllegroColor();

	if (m_sortMode == SpriteSortMode::IMMEDIATE) DrawFont(pDrawable);
	else m_drawables.push_back(pDrawable);
}

void SpriteBatch::DrawBitmap(Drawable* pDrawable)
{
	al_draw_tinted_scaled_rotated_bitmap_region(
		pDrawable->Type.pBitmap,
		pDrawable->Type.sx, pDrawable->Type.sy,
		pDrawable->Type.sw, pDrawable->Type.sh,
		pDrawable->color,
		pDrawable->Type.cx, pDrawable->Type.cy,
		pDrawable->x, pDrawable->y,
		pDrawable->Type.scx, pDrawable->Type.scy,
		pDrawable->Type.rotation, 0);
}

void SpriteBatch::DrawFont(Drawable* pDrawable)
{
	bool stored = pDrawable->Type.isTextStored;
	const char* text = stored
		? m_textCopies[pDrawable->Type.TextSource.index].c_str()
		: pDrawable->Type.TextSource.pText->c_str();

	al_draw_text(
		pDrawable->Type.pFont,
		pDrawable->color,
		pDrawable->x,
		pDrawable->y,
		0, text);
}