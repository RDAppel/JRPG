
#pragma once

class ScreenA : public Screen
{

private:

	Animation* m_pCurrent = nullptr;
	Animation* m_pWalkRight = nullptr;
	Animation* m_pWalkLeft = nullptr;
	Vector2 m_position = Vector2(300, 200);

public:

	ScreenA()
	{
		SetOnExit([]() { std::cout << "ScreenA exited" << std::endl; });
		SetOnRemove([this]() { GetScreenManager().AddScreen(*(new ScreenB)); });
	}


	virtual void LoadContent(ResourceManager& resourceManager)
	{
		std::string path;
		
		path = "Textures\\Spritesheets\\Characters\\Character_0001.png";
		Texture* pTexture = resourceManager.Load<Texture>(path);

		path = "Animations\\Characters\\WalkRight.anim";
		m_pWalkRight = resourceManager.Load<Animation>(path);
		m_pWalkRight->SetTexture(pTexture);

		path = "Animations\\Characters\\WalkLeft.anim";
		m_pWalkLeft = resourceManager.Load<Animation>(path);
		m_pWalkLeft->SetTexture(pTexture);

		m_pCurrent = m_pWalkRight;
	}

	virtual void UnloadContent() {}

	virtual void HandleInput(const InputState& input)
	{
		if (input.IsNewKeyPress(Key::A)) m_position.X += 30;
		if (input.IsNewKeyPress(Key::X)) Exit();

		if (m_pCurrent) m_pCurrent->Pause();
		if (input.IsKeyDown(Key::RIGHT))
		{
			m_pCurrent = m_pWalkRight;
			m_pCurrent->Play();
			m_position.X += 1;
		}
		if (input.IsKeyDown(Key::LEFT))
		{
			m_pCurrent = m_pWalkLeft;
			m_pCurrent->Play();
			m_position.X -= 1;
		}
	}

	virtual void Update(const GameTime& gameTime)
	{
	/*	double elapsed = gameTime.GetTimeElapsed();
		m_position += Vector2::GetRandom() * 60 * elapsed;*/

		m_pCurrent->Update(gameTime);
		Screen::Update(gameTime);
	}

	virtual void Draw(SpriteBatch& spriteBatch)
	{
		spriteBatch.Begin();
		spriteBatch.Draw(m_pCurrent, m_position);
		spriteBatch.End();
	}
};

