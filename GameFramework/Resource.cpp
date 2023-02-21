
#include "_PCH.h"

Resource::~Resource() { m_pResourceManager->RemoveResource(m_id); }

void Resource::SplitLine(const std::string& line, std::vector<std::string>& tokens,
	const char delimeter, bool trimTokens)
{
	std::stringstream ss(line);
	std::string token;

	while (std::getline(ss, token, delimeter))
	{
		if (trimTokens) Trim(token);
		tokens.push_back(token);
	}
}

void Resource::Trim(std::string& text, const std::string trimCharacters)
{
	text.erase(0, text.find_first_not_of(trimCharacters));
	text.erase(text.find_last_not_of(trimCharacters) + 1);
}