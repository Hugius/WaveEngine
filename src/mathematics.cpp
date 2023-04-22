#include "mathematics.hpp"

#include <cmath>

const vector<double> Mathematics::calculateDistributedPositions(const double start, const double range, const int count)
{
	const double step = range / static_cast<double>(count + 1);

	vector<double> positions = {};

	for(int index = 0; index < count; index++)
	{
		positions.push_back(start + step * static_cast<double>(index + 1));
	}

	return positions;
}

const dmat33 Mathematics::createTranslationMatrix(const double x, const double y)
{
	dmat33 result = dmat33(1.0);

	result.m[2][0] = x;
	result.m[2][1] = y;

	return result;
}

const dmat33 Mathematics::createScalingMatrix(const double x, const double y)
{
	dmat33 result = dmat33(1.0);

	result.m[0][0] = x;
	result.m[1][1] = y;

	return result;
}

const double Mathematics::getSignum(const double number)
{
	if(number < 0.0)
	{
		return -1.0;
	}

	if(number > 0.0)
	{
		return 1.0;
	}

	return 0.0;
}

const double Mathematics::getPi()
{
	return PI;
}