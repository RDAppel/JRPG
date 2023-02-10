
#include "_PCH.h"

const Color Color::WHITE = Color();
const Color Color::BLACK = Color(0, 0, 0);
const Color Color::RED = Color(1, 0, 0);
const Color Color::GREEN = Color(0, 1, 0);
const Color Color::BLUE = Color(0, 0, 1);

const Color Color::TRANSPARENT = Color(0, 0, 0, 0);

Color::Color(const float red, const float green, const float blue, const float alpha)
{
	R = red;
	G = green;
	B = blue;
	A = alpha;
}