
#include "_PCH.h"

#include "Character.h"
#include "MapComponent.h"

bool Character::Load(const std::string& path)
{
	std::ifstream fileIn(path.c_str(), std::ifstream::in);
	if (!fileIn.is_open() || !fileIn.good()) return false;

	std::vector<std::string> splitItems;
	Component::Type currentComponent = Component::Type::NONE;

	MapComponent* pMapComponent = nullptr;
	Texture* pTexture = nullptr;

	std::string line;
	while (getline(fileIn, line))
	{
		if (line.empty()) continue;

		Trim(line);
		if (line[0] == '#') continue;

		if (line == "Map Component" && !pMapComponent)
		{
			currentComponent = Component::Type::MAP;
			pMapComponent = new MapComponent;
			pMapComponent->m_pCharacter = this;
			m_components[Component::Type::MAP] = pMapComponent;
			continue;
		}
		if (line == "Dialog Component")
		{
			currentComponent = Component::Type::DIALOG;
			continue;
		}

		if (currentComponent == Component::Type::NONE) continue;

		splitItems.clear();
		SplitLine(line, splitItems, ':');
		if (splitItems.size() != 2) continue;

		std::string& key = splitItems[0];
		std::string& value = splitItems[1];

		if (currentComponent == Component::Type::MAP)
		{
			AnimationSet** pAnimationSet = nullptr;
			if (key == "Texture") pTexture = m_pResourceManager->Load<Texture>(value);
			if (key == "Idle") pAnimationSet = &pMapComponent->m_pIdleAnimations;
			if (key == "Walk") pAnimationSet = &pMapComponent->m_pWalkAnimations;
			if (key == "Run") pAnimationSet = &pMapComponent->m_pRunAnimations;
			if (pAnimationSet)
			{
				*pAnimationSet = m_pResourceManager->Load<AnimationSet>(value);
				if (*pAnimationSet && pTexture) (*pAnimationSet)->SetTexture(pTexture);
			}
		}

	}

	return true;
}

Component* Character::GetComponent(Component::Type type) const
{
	return m_components.at(type);
}