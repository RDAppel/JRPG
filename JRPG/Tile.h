#pragma once
#include "_PCH.h"

struct Tile
{
	static const int SIZE = 32;

	uint8_t tilesetIndex = 0;
	uint32_t tileIndex = 0;
};