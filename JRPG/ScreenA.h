
#pragma once

class ScreenA : public Screen
{

private:

	Texture* m_pTexture = nullptr;
	Vector2 m_position = Vector2(20, 20);

public:

	ScreenA()
	{
		SetOnExitCallback([]() { std::cout << "ScreenA exited" << std::endl; });
		SetOnRemoveCallback([this]() { GetScreenManager()->AddScreen(new ScreenB); });
	}


	virtual void LoadContent(ResourceManager* pResourceManager)
	{
		m_pTexture = pResourceManager->Load<Texture>("Textures\\Spritesheets\\Chest.png");
	}

	virtual void UnloadContent() {}

	virtual void HandleInput(const InputState* pInput)
	{
		if (pInput->IsNewKeyPress(Key::A)) m_position.X = 20;
		if (pInput->IsNewKeyPress(Key::X)) Exit();
	}

	virtual void Update(const GameTime* pGameTime)
	{
		m_position = Vector2::Lerp(Vector2::ZERO, Vector2::ONE * 200, pGameTime->GetTotalTime() / 5.0f);

		Screen::Update(pGameTime);
	}

	virtual void Draw(SpriteBatch* pSpriteBatch)
	{
		pSpriteBatch->Begin();
		pSpriteBatch->Draw(m_pTexture, m_position);
		pSpriteBatch->End();
	}
};

