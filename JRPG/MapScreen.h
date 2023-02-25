#pragma once

#include "_PCH.h"
#include "Map.h"

class MapScreen : public Screen
{

private:

	Map* m_pMap = nullptr;

public:


	MapScreen() {}

	virtual ~MapScreen() {}

	virtual void LoadContent(ResourceManager& resourceManager)
	{
		m_pMap = resourceManager
	}

	virtual void Update(GameTime& gameTime)
	{
	}

	virtual void Draw(SpriteBatch& spriteBatch)
	{
	}
};