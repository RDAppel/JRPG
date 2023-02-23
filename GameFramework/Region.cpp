
#include "_PCH.h"

std::ostream& operator<<(std::ostream& os, const Region& region)
{
	os << "{" << region.X << ", " << region.Y << ", " << region.Width << ", " << region.Height << "}";
	return os;
}

std::istream& operator>>(std::istream& is, Region& region)
{
	is >> region.X >> region.Y >> region.Width >> region.Height;
	return is;
}

