#pragma once

#include "_PCH.h"
#include "Map.h"

class MapScreen : public Screen
{

private:

	Map* m_pMap = nullptr;

	KeySequence m_consoleSequence;
	std::string m_consoleInput = "";

	ResourceManager* m_pResourceManager = nullptr;

public:

	MapScreen()
	{
		m_consoleSequence.SetKeys({ Key::ESCAPE, Key::ESCAPE });
		m_consoleSequence.SetTimePerKey(500);
		m_consoleSequence.SetOnComplete([this]() {
			if (GetScreenManager().GetGame().GetConsoleInput(m_consoleInput))
			{
				if (m_consoleInput.substr(0, 10) == "set scale ")
				{
					float scale = std::stof(m_consoleInput.substr(10));
					m_pMap->GetCamera().SetScale(Vector2::ONE * scale);
				}
			}
		});
	}

	virtual void LoadMap(const std::string& path)
	{
		if (m_pMap) m_pResourceManager->Remove(m_pMap);
		m_pMap = m_pResourceManager->Load<Map>(path);
	}

	virtual void LoadContent(ResourceManager& resourceManager) override
	{
		m_pResourceManager = &resourceManager;
		if (!m_pMap) LoadMap("test");
	}

	virtual void HandleInput(const InputState& inputState)
	{
		m_consoleSequence.HandleInput(inputState);
		if (m_pMap) m_pMap->HandleInput(inputState);
	}

	virtual void Update(const GameTime& gameTime) override
	{
		m_consoleSequence.Update(gameTime);
		if (m_pMap) m_pMap->Update(gameTime);
	}

	virtual void Draw(SpriteBatch& spriteBatch) override
	{
		if (m_pMap) m_pMap->Draw(spriteBatch);
	}

	virtual void SetMapComponent(MapComponent* pMapComponent)
	{
		if (m_pMap) m_pMap->SetMapComponent(pMapComponent);
	}

};

