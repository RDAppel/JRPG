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

	virtual Resource* Clone() { return nullptr; }

public:

	Resource() {}
	virtual ~Resource();

	virtual int GetId() const { return m_id; }

	virtual const std::string& GetPath() const { return m_path; }

	virtual bool IsCloneable() { return false; }

	virtual bool Load(const std::string& path) = 0;

	virtual void SplitLine(const std::string& line, std::vector<std::string>& tokens,
		const char delimeter = ',', bool trimTokens = true);

	virtual void Trim(std::string& text, const std::string trimCharacters = " \r\n\t");
};

