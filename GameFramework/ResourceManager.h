#pragma once

#include "_PCH.h"

class ResourceManager
{
private:

	int m_nextResourceId = 0;

	std::unordered_map<std::string, Resource*> m_resources;

	std::string m_contentPath = "";

	std::vector<Resource*> m_clones;

public:

	ResourceManager() { }

	void SetContentPath(const std::string& path) { m_contentPath = path; }

	void Remove(Resource *pResource)
	{
		for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
		{
			if (it->second == pResource)
			{
				m_resources.erase(it);
				return;
			}
		}

		for (auto it = m_clones.begin(); it != m_clones.end(); ++it)
		{
			if (*it == pResource)
			{
				m_clones.erase(it);
				return;
			}
		}
	}

	template <typename T>
	T* Load(const std::string& path, const bool cache = true, const bool appendContentPath = true)
	{
		if (m_resources.find(path) != m_resources.end())
		{
			Resource* pResource = m_resources[path];

			if (pResource->IsCloneable())
			{
				pResource = pResource->Clone();
				pResource->m_pResourceManager = this;
				pResource->m_id = m_nextResourceId;
				m_nextResourceId++;
				m_clones.push_back(pResource);
			}

			return static_cast<T*>(m_resources[path]);
		}

		T* pT = new T;
		pT->m_pResourceManager = this;
		pT->m_path = path;
		pT->m_id = m_nextResourceId;
		m_nextResourceId++;

		std::string fullPath = (appendContentPath ? m_contentPath : "").append(path);
		if (pT->Load(fullPath))
		{
			if (cache) m_resources[path] = pT;
			return pT;
		}

		delete pT;
		return nullptr;
	}

};