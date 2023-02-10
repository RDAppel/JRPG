
#include "_PCH.h"


void SpriteBatch::Begin(const SpriteSortMode sortMode,
	BlendState blendState)
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
}

void SpriteBatch::Draw(const Texture* pTexture, const Vector2 position, const Color color,
	const Vector2 origin, const Vector2 scale, const float rotation, const float drawDepth)
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
	pDrawable->Union.pBitmap = pTexture->GetAllegroBitmap();
	pDrawable->x = position.X;
	pDrawable->y = position.Y;
	pDrawable->color = color.GetAllegroColor();
	pDrawable->Union.sx = 0;
	pDrawable->Union.sy = 0;
	pDrawable->Union.sw = pTexture->GetWidth();
	pDrawable->Union.sh = pTexture->GetHeight();
	pDrawable->Union.cx = origin.X;
	pDrawable->Union.cy = origin.Y;
	pDrawable->Union.scx = scale.X;
	pDrawable->Union.scy = scale.Y;
	pDrawable->Union.rotation = rotation;
	pDrawable->depth = drawDepth;

	if (m_sortMode == SpriteSortMode::IMMEDIATE) DrawBitmap(pDrawable);
	else m_drawables.push_back(pDrawable);
}

void SpriteBatch::DrawBitmap(Drawable* pDrawable)
{
	al_draw_tinted_scaled_rotated_bitmap_region(
		pDrawable->Union.pBitmap,
		pDrawable->Union.sx, pDrawable->Union.sy,
		pDrawable->Union.sw, pDrawable->Union.sh,
		pDrawable->color,
		pDrawable->Union.cx, pDrawable->Union.cy,
		pDrawable->x, pDrawable->y,
		pDrawable->Union.scx, pDrawable->Union.scy,
		pDrawable->Union.rotation, 0);
}

void SpriteBatch::DrawFont(Drawable* pDrawable)
{
	//al_draw_text
}