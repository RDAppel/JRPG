#pragma once
#include "_PCH.h"

struct Tile
{
	static const int SIZE = 32;

	uint32_t TileIndex = 0;
	uint8_t TilesetIndex = 0;
	uint16_t X = 0;
	uint16_t Y = 0;
};