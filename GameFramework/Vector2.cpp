

#include "_PCH.h"

const Vector2 Vector2::ZERO = Vector2();
const Vector2 Vector2::ONE = Vector2(1, 1);
const Vector2 Vector2::UNIT_X = Vector2(1, 0);
const Vector2 Vector2::UNIT_Y = Vector2(0, 1);

float Vector2::Length() const
{
	return sqrtf(X * X + Y * Y);
}

float Vector2::LengthSquared() const
{
	return X * X + Y * Y;
}

float Vector2::Distance(const Vector2& other) const
{
	return sqrtf((X - other.X) * (X - other.X) + (Y - other.Y) * (Y - other.Y));
}

float Vector2::DistanceSquared(const Vector2& other) const
{
	return (X - other.X) * (X - other.X) + (Y - other.Y) * (Y - other.Y);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-X, -Y);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(X + other.X, Y + other.Y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(X - other.X, Y - other.Y);
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2(X * other.X, Y * other.Y);
}

Vector2 Vector2::operator/(const Vector2& other) const
{
	return Vector2(X / other.X, Y / other.Y);
}

Vector2 Vector2::operator*(const float scalar) const
{
	return Vector2(X * scalar, Y * scalar);
}	

Vector2 Vector2::operator/(const float scalar) const
{
	return Vector2(X / scalar, Y / scalar);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	X += other.X;
	Y += other.Y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	X -= other.X;
	Y -= other.Y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	X *= other.X;
	Y *= other.Y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	X /= other.X;
	Y /= other.Y;
	return *this;
}

Vector2& Vector2::operator*=(const float scalar)
{
	X *= scalar;
	Y *= scalar;
	return *this;
}	

Vector2& Vector2::operator/=(const float scalar)
{
	X /= scalar;
	Y /= scalar;
	return *this;
}

void Vector2::Normalize()
{
	if (!IsZero())
	{
		float length = Length();
		X /= length;
		Y /= length;
	}
}

Vector2 Vector2::GetNormal() const
{
	if (!IsZero())
	{
		float length = Length();
		return Vector2(X / length, Y / length);
	}
	else return Vector2::ZERO;
}

float Vector2::DotProduct(const Vector2& other) const
{
	return X * other.X + Y * other.Y;
}

float Vector2::CrossProduct(const Vector2& other) const
{
	return X * other.Y - Y * other.X;
}

bool Vector2::operator==(const Vector2& other) const
{
	return X == other.X && Y == other.Y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return X != other.X || Y != other.Y;
}

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end,
	const float value, const bool clamp)
{
	return start + (end - start) * (clamp ? Math::Clamp(value) : value);
}

Vector2 Vector2::GetRandom()
{
	float angle = Math::GetRandomFloat() * (2 * Math::PI);
	return Vector2(cosf(angle), sinf(angle));
}

std::string Vector2::ToString() const
{
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

Vector2 operator*(const float scalar, const Vector2& vector)
{
	return Vector2(vector.X * scalar, vector.Y * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector2& vector)
{
	os << "{" << vector.X << ", " << vector.Y << "}";
	return os;
}

std::istream& operator>>(std::istream& is, Vector2& vector)
{
	is >> vector.X >> vector.Y;
	return is;
}

