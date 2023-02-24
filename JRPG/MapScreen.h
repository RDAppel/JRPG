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
				const uint8_t COUNT = 3;
				std::string commands[COUNT] = {
					"set scale",
					"fill background",
					"print map",
				};

				for (uint8_t i = 0; i < COUNT; ++i)
				{
					if (m_consoleInput.substr(0, commands[i].length()) == commands[i])
					{
						if (i == 0)
						{
							std::string args = m_consoleInput.substr(commands[i].length() + 1);
							m_pMap->GetCamera().SetScale(Vector2::ONE * std::stof(args));
						}
						else if (i == 2)
						{
							m_pMap->PrintToConsole();
						}
					}
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
		if (!m_pMap) LoadMap("Maps\\Test_01.map");
	}

	virtual void HandleInput(const InputState& inputState)
	{
		m_consoleSequence.HandleInput(inputState);

		if (!m_pMap) return;

		//std::cout << inputState.GetMousePosition() << "\n";
		Vector2 mousePosition = inputState.GetMousePosition();
		Vector2 worldPosition = m_pMap->GetCamera().GetScreenToWorldPosition(mousePosition) / Tile::SIZE;

		//std::cout << (int)worldPosition.X << ", " << (int)worldPosition.Y << "\n";

		if (inputState.IsMouseButtonDown(MouseButton::LEFT))
		{
			Tile tile;
			tile.X = (int)worldPosition.X;
			tile.Y = (int)worldPosition.Y;
			tile.TilesetIndex = 0;
			tile.TileIndex = Math::GetRandomInt(0, 4);
			m_pMap->AddTileAtPosition(0, tile);
		}
		

		m_pMap->HandleInput(inputState);
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

