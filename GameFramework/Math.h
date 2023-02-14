#pragma once

class Math
{

public:

	static const float PI;
	static const float NORMALIZE_PI_OVER4;

	static float Lerp(const float start, const float end,
		const float value, const bool clamp = false);

	static int GetRandomInt(const int min = 0, const int max = RAND_MAX);

	static float GetRandomFloat() { return ((float)rand() / RAND_MAX); }

	static float Clamp(const float value, const float min = 0, const float max = 1);
};

