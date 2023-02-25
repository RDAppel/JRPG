#pragma once

#include "_PCH.h"

struct Tile
{
	uint8_t X;
	uint8_t Y;
	uint8_t TilesetIndex;
	uint32_t TileIndex; // todo: memory optimizaion?
};