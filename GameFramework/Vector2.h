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

	void Set(const float x, const float y) { X = x; Y = y; }
	void Set(const float array[2]) { X = array[0]; Y = array[1]; }

	float Length() const;
	float LengthSquared() const;
	float Distance(const Vector2& other) const;
	float DistanceSquared(const Vector2& other) const;

	Vector2 operator-() const;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const float scalar) const;
	Vector2 operator/(const float scalar) const;

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(const float scalar);
	Vector2& operator/=(const float scalar);

	void Normalize();
	Vector2 GetNormal() const;

	float DotProduct(const Vector2& other) const;
	float CrossProduct(const Vector2& other) const;

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	bool IsZero() const { return X == 0 && Y == 0; }

	Vector2 Left() const { return Vector2(-Y, X); }
	Vector2 Right() const { return Vector2(Y, -X); }

	std::string ToString() const;


	static Vector2 Lerp(const Vector2& start, const Vector2& end, const float value, bool clamp = false);
	static Vector2 GetRandom();

};


Vector2 operator*(const float scalar, const Vector2& vector);

std::ostream& operator<<(std::ostream& os, const Vector2& vector);

std::istream& operator>>(std::istream& is, Vector2& vector);

