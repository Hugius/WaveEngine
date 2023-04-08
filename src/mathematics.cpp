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

const fmat33 Mathematics::createTranslationMatrix(const double x, const double y)
{
	fmat33 result = fmat33(1.0f);

	result.m[2][0] = x;
	result.m[2][1] = y;

	return result;
}

const fmat33 Mathematics::createRotationMatrix(const double angle)
{
	fmat33 result = fmat33(1.0f);

	result.m[0][0] = cos(angle);
	result.m[1][0] = -sin(angle);
	result.m[0][1] = sin(angle);
	result.m[1][1] = cos(angle);

	return result;
}

const fmat33 Mathematics::createScalingMatrix(const double x, const double y)
{
	fmat33 result = fmat33(1.0f);

	result.m[0][0] = x;
	result.m[1][1] = y;

	return result;
}

const double Mathematics::convertToRadians(const double angle)
{
	return (angle * DEG2RAD);
}

const double Mathematics::limitAngle(const double angle)
{
	if(angle < 0.0f)
	{
		return (360.0f - fabsf(fmodf(angle, 360.0f)));
	}
	else
	{
		return fmodf(angle, 360.0f);
	}
}

const double Mathematics::getSignum(double value)
{
	if(value < 0.0f)
	{
		return -1.0f;
	}

	if(value > 0.0f)
	{
		return 1.0f;
	}

	return 0.0f;
}

const double Mathematics::getPi()
{
	return PI;
}