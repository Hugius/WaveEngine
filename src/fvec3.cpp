#pragma warning(disable:26495)

#include "fvec3.hpp"

fvec3::fvec3(const float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

fvec3::fvec3(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}