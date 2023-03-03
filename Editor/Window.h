#pragma once

#include "..\RPGLibrary\_PCH.h"


class Window
{

private:

protected:

	bool m_isOpen = true;

public:

	virtual void LoadContent(ResourceManager& resourceManager) { } 

	virtual void Update(const GameTime& gameTime) = 0;

};