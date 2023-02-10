#pragma once

#include <string>

class Resource
{

	friend class ResourceManager;

private:

	int m_id = -1;

public:

	virtual bool IsCloneable() { return true; }

	virtual bool Load(const std::string& path) = 0;
};

