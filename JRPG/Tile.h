#pragma once

#include "_PCH.h"

struct Tile
{
	static const uint8_t SIZE = 32;

	uint8_t X;
	uint8_t Y;
	uint8_t TilesetIndex;
	uint32_t TileIndex; // todo: memory optimizaion?
};