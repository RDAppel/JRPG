#pragma once

#include "_PCH.h"

class Resource
{

	friend class ResourceManager;

private:

	int m_id = -1;

protected:

	std::string m_path = "";

	ResourceManager* m_pResourceManager = nullptr;

public:

	virtual bool IsCloneable() { return false; }

	virtual Resource* Clone() { return nullptr; }

	virtual bool Load(const std::string& path) = 0;

	virtual void SplitLine(const std::string& line, std::vector<std::string>& tokens,
		const char delimeter = ',', bool trimTokens = true)
	{
		std::stringstream ss(line);
		std::string token;

		while (std::getline(ss, token, delimeter))
		{
			if (trimTokens) Trim(token);
			tokens.push_back(token);
		}
	}

	virtual void Trim(std::string& text, const std::string trimCharacters = " \r\n\t")
	{
		text.erase(0, text.find_first_not_of(trimCharacters));
		text.erase(text.find_last_not_of(trimCharacters) + 1);
	}
};

