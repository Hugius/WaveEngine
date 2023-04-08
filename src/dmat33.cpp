#include "dmat33.hpp"

dmat33::dmat33(const double value)
{
	for(int index = 0; index < 9; index++)
	{
		f[index] = 0.0;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
}

const dmat33 dmat33::operator*(const dmat33 & other) const
{
	dmat33 result = dmat33(1.0);

	for(int column = 0; column < 3; column++)
	{
		for(int row = 0; row < 3; row++)
		{
			result.m[row][column] = 0.0;

			for(int inner = 0; inner < 3; inner++)
			{
				result.m[row][column] += (this->m[inner][column] * other.m[row][inner]);
			}
		}
	}

	return result;
}

const dvec2 dmat33::operator*(const dvec2 & other) const
{
	dvec2 result = dvec2(0.0);

	result.x = (this->m[0][0] * other.x) + (this->m[1][0] * other.y);
	result.y = (this->m[0][1] * other.x) + (this->m[1][1] * other.y);

	return result;
}