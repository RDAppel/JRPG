#pragma once

class Color
{

public:

	float R = 1.0f;
	float G = 1.0f;
	float B = 1.0f;
	float A = 1.0f;

	static const Color WHITE;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;

	static const Color TRANSPARENT;

	Color(const float red = 1.0f, const float green = 1.0f, const float blue = 1.0f, const float alpha = 1.0f);

	ALLEGRO_COLOR GetAllegroColor() const { return al_map_rgba_f(R, G, B, A); }
};

