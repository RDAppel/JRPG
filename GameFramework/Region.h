#pragma once

class Region
{

public:

	int X = 0;
	int Y = 0;
	int Width = 0;
	int Height = 0;

	Region() { }
	Region(const int x, const int y, const int width, const int height)
	{
		X = x; Y = y; Width = width; Height = height;
	}
	Region(const Region& other)
	{
		X = other.X; Y = other.Y; Width = other.Width; Height = other.Height;
	}

	Vector2 GetSize() const { return Vector2(Width, Height); }

};

