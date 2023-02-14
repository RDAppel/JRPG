#pragma once

class ScreenB : public Screen
{

private:

	Font* m_pFont = nullptr;


public:


	virtual void LoadContent(ResourceManager* pResourceManager)
	{
		m_pFont = pResourceManager->Load<Font>("Fonts\\Iceland.ttf");
	}

	virtual void UnloadContent() {} 

	virtual void HandleInput(const InputState* pInput) {}

	virtual void Update(const GameTime* pGameTime) {}

	virtual void Draw(SpriteBatch* pSpriteBatch)
	{
		std::string text = "Hello!!!";
		pSpriteBatch->Begin();
		pSpriteBatch->Draw(m_pFont, &text, Vector2(400, 400), Color::RED);
		pSpriteBatch->Draw(m_pFont, "what up?", Vector2(400, 450), Color::RED);
		pSpriteBatch->End();
	}

	virtual bool ShouldDrawBelow() { return true; }

	virtual bool ShouldUpdateBelow() { return true; }

	virtual bool ShouldHandleInputBelow() { return true; }
};

