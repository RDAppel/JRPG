
#pragma once

class ScreenA : public Screen
{

private:

	Texture *m_pTexture = nullptr;
	Vector2 m_position = Vector2(20, 20);

public:


	virtual void LoadContent(ResourceManager* pResourceManager)
	{
		m_pTexture = pResourceManager->Load<Texture>("Textures\\Spritesheets\\Chest.png");
	}

	virtual void UnloadContent() { }

	virtual void HandleInput(const InputState* pInput)
	{
		if (pInput->IsNewKeyPress(Key::A)) m_position.X = 20;
		if (pInput->IsNewKeyPress(Key::B))
		{
			GetScreenManager()->AddScreen(new ScreenB);
		}
	}

	virtual void Update(const GameTime* pGameTime)
	{
		m_position.X += pGameTime->GetTimeElapsed() * 100;
	}

	virtual void Draw(SpriteBatch* pSpriteBatch)
	{
		pSpriteBatch->Begin();
		pSpriteBatch->Draw(m_pTexture, m_position);
		pSpriteBatch->End();
	}


};

