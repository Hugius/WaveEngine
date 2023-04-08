#include "ivec2.hpp"
#include "fvec2.hpp"

ivec2::ivec2(const fvec2 & other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
}

ivec2::ivec2(const int value)
{
	this->x = value;
	this->y = value;
}

ivec2::ivec2(const int x, const int y)
{
	this->x = x;
	this->y = y;
}

const ivec2 ivec2::operator-(const ivec2 & other)const
{
	return ivec2((this->x - other.x), (this->y - other.y));
}

const ivec2 ivec2::operator/(const int other) const
{
	return ivec2((this->x / other), (this->y / other));
}