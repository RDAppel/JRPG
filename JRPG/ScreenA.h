
#pragma once

class ScreenA : public Screen
{

private:

	//Animation* m_pCurrent = nullptr;
	//Animation* m_pWalkRight = nullptr;
	//Animation* m_pWalkLeft = nullptr;
	//Vector2 m_position = Vector2(300, 200);

	Character* m_pCharacter = nullptr;
	MapComponent* m_pMC = nullptr;

public:

	ScreenA()
	{
		SetOnExit([]() { std::cout << "ScreenA exited" << std::endl; });
		SetOnRemove([this]() { GetScreenManager().AddScreen(*(new ScreenB)); });
	}


	virtual void LoadContent(ResourceManager& resourceManager)
	{
		m_pCharacter = new Character;
		m_pMC = new MapComponent;

		std::string path;
		Texture* pTexture;
		Animation* pAnimation;

		path = "Textures\\Spritesheets\\Characters\\Character_0002.png";
		pTexture = resourceManager.Load<Texture>(path);

		path = "Animations\\Characters\\Idle\\Up.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_idleAnimations[Direction::UP] = pAnimation;

		path = "Animations\\Characters\\Idle\\Down.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_idleAnimations[Direction::DOWN] = pAnimation;

		path = "Animations\\Characters\\Idle\\Left.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_idleAnimations[Direction::LEFT] = pAnimation;

		path = "Animations\\Characters\\Idle\\Right.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_idleAnimations[Direction::RIGHT] = pAnimation;

		path = "Animations\\Characters\\Walk\\Up.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_walkAnimations[Direction::UP] = pAnimation;

		path = "Animations\\Characters\\Walk\\Down.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_walkAnimations[Direction::DOWN] = pAnimation;

		path = "Animations\\Characters\\Walk\\Left.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_walkAnimations[Direction::LEFT] = pAnimation;

		path = "Animations\\Characters\\Walk\\Right.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_walkAnimations[Direction::RIGHT] = pAnimation;

		path = "Animations\\Characters\\Run\\Up.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_runAnimations[Direction::UP] = pAnimation;

		path = "Animations\\Characters\\Run\\Down.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_runAnimations[Direction::DOWN] = pAnimation;

		path = "Animations\\Characters\\Run\\Left.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_runAnimations[Direction::LEFT] = pAnimation;

		path = "Animations\\Characters\\Run\\Right.anim";
		pAnimation = resourceManager.Load<Animation>(path);
		pAnimation->SetTexture(pTexture);
		m_pMC->m_runAnimations[Direction::RIGHT] = pAnimation;

	}

	virtual void UnloadContent() {}

	virtual void HandleInput(const InputState& input)
	{
		if (input.IsNewKeyPress(Key::X)) Exit();

		m_pMC->HandleInput(input);
		/*if (input.IsKeyDown(Key::RIGHT))
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
		}*/
	}

	virtual void Update(const GameTime& gameTime)
	{
		/*	double elapsed = gameTime.GetTimeElapsed();
			m_position += Vector2::GetRandom() * 60 * elapsed;*/

		m_pMC->Update(gameTime);
		Screen::Update(gameTime);
	}

	virtual void Draw(SpriteBatch& spriteBatch)
	{
		ALLEGRO_TRANSFORM identity;
		ALLEGRO_TRANSFORM scale;
		al_identity_transform(&identity);
		al_identity_transform(&scale);
		al_scale_transform(&scale, 2, 2);

		al_use_transform(&scale);
		spriteBatch.Begin();
		//spriteBatch.Draw(m_pCurrent, m_position);
		m_pMC->Draw(spriteBatch);
		spriteBatch.End();
		al_use_transform(&identity);
	}
};

