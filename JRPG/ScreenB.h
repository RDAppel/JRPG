#pragma once

class ScreenB : public Screen
{

private:

	Font* m_pFont = nullptr;

	KeySequence m_sequence;

	std::string m_inputText = "";

public:

	ScreenB()
	{
		m_sequence.SetKeys({ Key::ESCAPE, Key::ESCAPE });
		m_sequence.SetTimePerKey(500);
		m_sequence.SetOnComplete([this]() {
			if (GetScreenManager().GetGame().GetConsoleInput(m_inputText))
			{
				
			}
		});
	}


	virtual void LoadContent(ResourceManager& resourceManager)
	{
		m_pFont = resourceManager.Load<Font>("Fonts\\Iceland.ttf");
	}

	virtual void UnloadContent() {}

	virtual void HandleInput(const InputState& input)
	{

		m_sequence.HandleInput(input);
	}

	virtual void Update(const GameTime& gameTime)
	{

		m_sequence.Update(gameTime);
	}

	virtual void Draw(SpriteBatch& spriteBatch)
	{
		spriteBatch.Begin();

		if (m_inputText != "")
		{
			spriteBatch.Draw(m_pFont, &m_inputText, Vector2(400, 200), Color::RED);
		}

		spriteBatch.Draw(m_pFont, "what up?", Vector2(400, 250), Color::RED);
		spriteBatch.End();
	}

	virtual bool ShouldDrawBelow() { return true; }

	virtual bool ShouldUpdateBelow() { return true; }

	virtual bool ShouldHandleInputBelow() { return true; }
};

