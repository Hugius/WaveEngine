#include "mathematics.hpp"

#include <cmath>

const vector<double> Mathematics::calculateDistributedPositions(const double start, const double range, const int count, const bool mustIncludeFirst, const bool mustIncludeLast)
{
	int stepOffset;
	int indexOffset;

	if(mustIncludeFirst && mustIncludeLast)
	{
		stepOffset = -1;
		indexOffset = 0;
	}
	else if(mustIncludeFirst && !mustIncludeLast)
	{
		stepOffset = 0;
		indexOffset = 0;
	}
	else if(!mustIncludeFirst && mustIncludeLast)
	{
		stepOffset = -1;
		indexOffset = 1;
	}
	else
	{
		stepOffset = 1;
		indexOffset = 1;
	}

	const double step = range / static_cast<double>(count + stepOffset);

	vector<double> positions = {};

	for(int index = 0; index < count; index++)
	{
		positions.push_back(start + step * static_cast<double>(index + indexOffset));
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