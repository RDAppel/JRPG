#pragma once

#include "MapScreen.h"
#include "Character.h"

class JRPG : public Game
{

private:

	Character* m_pCharacter = nullptr;

public:

	JRPG()
	{
		SetRequireVSync(true);
		SetTargetFramesPerSecond(60);
		SetClearColor(Color::BLACK);
	}

	virtual void LoadContent(ResourceManager& resourceManager) override
	{
		// todo: move the character loading stuff to a loading screen
		m_pCharacter = resourceManager.Load<Character>("Characters\\Playable\\PC_0001.char");
		Component* pComponent = m_pCharacter->GetComponent(Component::Type::MAP);
		MapScreen *pMapScreen = new MapScreen;
		GetScreenManager().AddScreen(pMapScreen);
		pMapScreen->SetMapComponent(dynamic_cast<MapComponent*>(pComponent));
	}
};

