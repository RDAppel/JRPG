
#include "_PCH.h"

const float Math::PI = 3.14159265358979323846f;
const float Math::NORMALIZE_PI_OVER4 = 0.70710678119f;

float Math::Clamp(const float value, const float min, const float max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

float Math::Lerp(const float start, const float end,
	const float value, const bool clamp)
{
	return start + (end - start) * (clamp ? Clamp(value) : value);
}

int Math::GetRandomInt(const int min, const int max)
{
	return min + (rand() % (max - min));
}