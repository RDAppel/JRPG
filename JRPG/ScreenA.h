
#pragma once

class ScreenA : public Screen
{

private:

	Texture* m_pTexture = nullptr;
	Vector2 m_position = Vector2(600, 400);

public:

	ScreenA()
	{
		SetOnExit([]() { std::cout << "ScreenA exited" << std::endl; });
		SetOnRemove([this]() { GetScreenManager().AddScreen(*(new ScreenB)); });
	}


	virtual void LoadContent(ResourceManager& resourceManager)
	{
		m_pTexture = resourceManager.Load<Texture>("Textures\\Spritesheets\\Chest.png");
	}

	virtual void UnloadContent() {}

	virtual void HandleInput(const InputState& input)
	{
		if (input.IsNewKeyPress(Key::A)) m_position.X += 30;
		if (input.IsNewKeyPress(Key::X)) Exit();
	}

	virtual void Update(const GameTime& gameTime)
	{
		double elapsed = gameTime.GetTimeElapsed();
		m_position += Vector2::GetRandom() * 60 * elapsed;
		Screen::Update(gameTime);
	}

	virtual void Draw(SpriteBatch& spriteBatch)
	{
		spriteBatch.Begin();
		spriteBatch.Draw(m_pTexture, m_position);
		spriteBatch.End();
	}
};

