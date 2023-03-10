
#pragma once

#include "Tile.h"

class Layer
{

public:

	enum class Type :uint8_t { NONE, BACKGROUND, INTERACTION, FOREGROUND };

private:

	std::vector<Tile> m_tiles;

	Type m_type = Type::BACKGROUND;

public:

	static const std::string& GetNameOfType(const Type type)
	{
		static const std::string names[] = { "None", "Background", "Interaction", "Foreground" };
		return names[(int)type];
	}

	static const Type& GetTypeByName(const std::string& name)
	{
		static const std::map<std::string, Type> types = {
			{ "None", Type::NONE },
			{ "Background", Type::BACKGROUND },
			{ "Interaction", Type::INTERACTION },
			{ "Foreground", Type::FOREGROUND }
		};

		return types.at(name);
	}

	Layer() {}
	Layer(const Layer&) = delete;
	virtual ~Layer() {}

	Layer& operator=(const Layer&) = delete;

	virtual Type GetType() const { return m_type; }

	virtual void SetType(Type type) { m_type = type; }

	virtual void AddTile(const Tile tile) { m_tiles.push_back(tile); }

	virtual Tile& operator[](const int index) { return m_tiles[index]; }
	virtual const Tile& operator[](const int index) const { return m_tiles[index]; }

	virtual size_t GetSize() const { return m_tiles.size(); }

	virtual std::vector<Tile>::iterator begin() { return m_tiles.begin(); }
	virtual std::vector<Tile>::iterator end() { return m_tiles.end(); }

};

