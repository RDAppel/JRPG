#pragma once

#include "Tile.h"

class Layer
{

public:

	enum class Type : uint8_t { BACKGROUND, INTERACTION, FOREGROUND };

private:

	Type m_type = Type::BACKGROUND;

	std::vector<Tile> m_tiles;

public:

	Layer() {}
	Layer(const Layer&) = delete;
	virtual ~Layer() {}

	Layer& operator=(const Layer&) = delete;

	virtual Type GetType() const { return m_type; }
	virtual void SetType(const Type type) { m_type = type; }

	virtual const Tile& operator[](size_t index) const { return m_tiles[index]; }
	virtual Tile& operator[](size_t index) { return m_tiles[index]; }

	virtual size_t GetSize() const { return m_tiles.size(); }

	virtual void AddTile(const uint8_t tilesetIndex, const uint32_t tileIndex)
	{ 
		m_tiles.push_back(Tile{ tilesetIndex, tileIndex });
	}

	// iterators
	virtual std::vector<Tile>::iterator begin() { return m_tiles.begin(); }
	virtual std::vector<Tile>::iterator end() { return m_tiles.end(); }

};

