#include "dvec2.hpp"
#include "ivec2.hpp"

dvec2::dvec2(const double value)
{
	this->x = value;
	this->y = value;
}

dvec2::dvec2(const double x, const double y)
{
	this->x = x;
	this->y = y;
}

dvec2::dvec2(const ivec2 & other)
{
	this->x = static_cast<double>(other.x);
	this->y = static_cast<double>(other.y);
}

void dvec2::operator+=(const dvec2 & other)
{
	this->x += other.x;
	this->y += other.y;
}

const dvec2 dvec2::operator+(const dvec2 & other)const
{
	return dvec2(this->x + other.x, this->y + other.y);
}

const dvec2 dvec2::operator*(const dvec2 & other)const
{
	return dvec2(this->x * other.x, this->y * other.y);
}

const bool dvec2::operator<(const dvec2 & other) const
{
	return this->x < other.x && this->y < other.y;
}

const bool dvec2::operator>(const dvec2 & other) const
{
	return this->x > other.x && this->y > other.y;
}