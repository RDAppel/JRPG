#pragma once

#include "_PCH.h"

class ResourceManager
{
private:

	int m_nextResourceId = 0;

	std::map<std::string, Resource*> m_resources;

	std::string m_contentPath = "";

	std::vector<Resource*> m_clones;


public:

	ResourceManager() { }

	void SetContentPath(const std::string& path) { m_contentPath = path; }


	template <typename T>
	T* Load(const std::string& path, const bool cache = true, const bool appendContentPath = true)
	{
		if (m_resources.find(path) != m_resources.end())
		{
			T* pResource = dynamic_cast<T*>(m_resources[path]);

			if (pResource->IsCloneable())
			{
				// todo: call clone...
					
			}

			return pResource;
		}

		T* pT = new T;

		std::string fullPath = (appendContentPath ? m_contentPath : "").append(path);
		if (pT->Load(fullPath))
		{
			if (cache) m_resources[path] = pT;
			pT->m_id = m_nextResourceId;
			m_nextResourceId++;

			return pT;
		}

		delete pT;
		return nullptr;
	}

};