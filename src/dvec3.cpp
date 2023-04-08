#pragma warning(disable:26495)

#include "dvec3.hpp"

dvec3::dvec3(const double value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

dvec3::dvec3(const double x, const double y, const double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}