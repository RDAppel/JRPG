
#pragma once

enum class SpriteSortMode
{
	BACK_TO_FRONT,
	DEFERRED,
	FRONT_TO_BACK,
	IMMEDIATE,
	TEXTURE
};

enum class BlendState
{
	ALPHA,
	ADDITIVE
};

class SpriteBatch
{


private:

	struct Drawable
	{
		bool isBitmap = false;
		ALLEGRO_COLOR color = ALLEGRO_COLOR{};
		int x = 0;
		int y = 0;
		float depth = 0;

		//pDrawable->Union.pBitmap,

		union
		{
			struct // bitmap
			{
				ALLEGRO_BITMAP* pBitmap;
				int sx; int sy;
				int sw; int sh;
				int cx; int cy;
				float scx; float scy;
				float rotation;
			};

			struct // font
			{
				bool isTextStored;
				ALLEGRO_FONT* pFont;

				union
				{
					std::string* pText;
					unsigned int index;
				} TextSource;
			};
		} Type = { };

		bool operator<(const Drawable& other) const { return depth < other.depth; }
	};

	struct Compare
	{
		struct FrontToBack
		{
			bool operator()(const Drawable* l, const Drawable* r) { return l < r; }
		};

		struct BackToFront
		{
			bool operator()(const Drawable* l, const Drawable* r) { return l < r; }
		};
	};

	bool m_isStarted = false;

	SpriteSortMode m_sortMode = SpriteSortMode::DEFERRED;

	std::vector<Drawable*> m_drawables;
	std::vector<Drawable*> m_inactiveDrawables;
	std::vector<Drawable*>::iterator m_it;

	std::vector<std::string> m_textCopies;

	void DrawBitmap(Drawable*);
	void DrawFont(Drawable*);
	
public:

	virtual void Begin(const SpriteSortMode sortMode = SpriteSortMode::DEFERRED,
		BlendState blendState = BlendState::ALPHA);

	virtual void End();

	virtual void Draw(const Texture* pTexture, const Vector2 position, const Color color = Color::WHITE,
		const Vector2 origin = Vector2::ZERO, const Vector2 scale = Vector2::ONE, const float rotation = 0,
		const float drawDepth = 0);

	virtual void Draw(const Texture* pTexture, const Vector2 position, const Region& source,
		const Color color = Color::WHITE, const Vector2 origin = Vector2::ZERO,
		const Vector2 scale = Vector2::ONE, const float rotation = 0, const float drawDepth = 0);

	virtual void Draw(const Animation* pAnimation, const Vector2 position, const Color color = Color::WHITE,
		const Vector2 origin = Vector2::ZERO, const Vector2 scale = Vector2::ONE, const float rotation = 0,
		const float drawDepth = 0);

	virtual void Draw(const Font* pFont, std::string pText, const Vector2 position,
		const Color color = Color::WHITE, const float drawDepth = 0);

	virtual void Draw(const Font* pFont, std::string* pText, const Vector2 position,
		const Color color = Color::WHITE, const float drawDepth = 0);

};