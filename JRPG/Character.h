#pragma once

#include "_PCH.h"

#include "Component.h"

class Character : public Resource
{

private:

	std::string m_name;

	std::unordered_map<Component::Type, Component*> m_components;

public:

	//// todo: make this private once the character gets loaded through the resource mgr.
	//virtual void AddComponent(Component* pComponent);

	Character() {}
	Character(const Character&) = delete;
	virtual ~Character() {}

	Character& operator=(const Character&) = delete;

	virtual bool Load(const std::string& path);

	virtual Component* GetComponent(Component::Type type) const;


};

