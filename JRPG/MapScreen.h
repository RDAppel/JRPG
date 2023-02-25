#pragma once

#include "_PCH.h"
#include "Map.h"

class MapScreen : public Screen
{

private:

	Map* m_pMap = nullptr;

	ResourceManager* m_pResourceManager = nullptr;

public:

	MapScreen() {}

	virtual ~MapScreen() {}

	virtual void LoadMap(const std::string& path)
	{
		if (m_pMap) delete m_pMap;
		m_pMap = m_pResourceManager->Load<Map>(path);
	}

	virtual void LoadContent(ResourceManager& resourceManager)
	{
		m_pResourceManager = &resourceManager;
		LoadMap("Maps\\Test_01.map");
	}

	virtual void HandleInput(const InputState& inputState)
	{
		 if (!m_pMap) return;
		 m_pMap->HandleInput(inputState);
	}

	virtual void Update(const GameTime& gameTime)
	{
		if (!m_pMap) return;
		m_pMap->Update(gameTime);
	}	

	virtual void Draw(SpriteBatch& spriteBatch)
	{
		if (!m_pMap) return;
		m_pMap->Draw(spriteBatch);
	}

	virtual void SetMapComponent(MapComponent* pMapComponent)
	{
		if (m_pMap) m_pMap->SetMapComponent(pMapComponent);
	}
};

