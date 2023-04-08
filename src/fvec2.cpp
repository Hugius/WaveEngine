#include "fvec2.hpp"
#include "ivec2.hpp"

fvec2::fvec2(const float value)
{
	this->x = value;
	this->y = value;
}

fvec2::fvec2(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

fvec2::fvec2(const ivec2 & other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
}

void fvec2::operator+=(const fvec2 & v)
{
	this->x += v.x;
	this->y += v.y;
}

const fvec2 fvec2::operator+(const fvec2 & v)const
{
	return fvec2((this->x + v.x), (this->y + v.y));
}

const fvec2 fvec2::operator*(const fvec2 & v)const
{
	return fvec2((this->x * v.x), (this->y * v.y));
}