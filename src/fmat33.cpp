#include "fmat33.hpp"

fmat33::fmat33(const float value)
{
	for(int index = 0; index < 9; index++)
	{
		f[index] = 0.0f;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
}

const fmat33 fmat33::operator*(const fmat33 & other) const
{
	fmat33 result = fmat33(1.0f);

	for(int column = 0; column < 3; column++)
	{
		for(int row = 0; row < 3; row++)
		{
			result.m[row][column] = 0.0f;

			for(int inner = 0; inner < 3; inner++)
			{
				result.m[row][column] += (this->m[inner][column] * other.m[row][inner]);
			}
		}
	}

	return result;
}

const fvec2 fmat33::operator*(const fvec2 & other) const
{
	fvec2 result = fvec2(0.0f);

	result.x = (this->m[0][0] * other.x) + (this->m[1][0] * other.y);
	result.y = (this->m[0][1] * other.x) + (this->m[1][1] * other.y);

	return result;
}