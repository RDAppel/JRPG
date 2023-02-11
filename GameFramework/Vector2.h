#pragma once
class Vector2
{

public:

	static const Vector2 ZERO;
	static const Vector2 ONE;
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;

	float X = 0;
	float Y = 0;

	Vector2(const float x = 0, const float y = 0) { X = x; Y = y; }
	Vector2(const float array[2]) { X = array[0]; Y = array[1]; }

};

