#include "mathematics.hpp"

#include <cmath>

const vector<float> Mathematics::calculateDistributedPositions(const float start, const float range, const int count)
{
	const float step = range / static_cast<float>(count + 1);

	vector<float> positions = {};

	for(int index = 0; index < count; index++)
	{
		positions.push_back(start + step * static_cast<float>(index + 1));
	}

	return positions;
}

const fmat33 Mathematics::createTranslationMatrix(const float x, const float y)
{
	fmat33 result = fmat33(1.0f);

	result.m[2][0] = x;
	result.m[2][1] = y;

	return result;
}

const fmat33 Mathematics::createRotationMatrix(const float angle)
{
	fmat33 result = fmat33(1.0f);

	result.m[0][0] = cos(angle);
	result.m[1][0] = -sin(angle);
	result.m[0][1] = sin(angle);
	result.m[1][1] = cos(angle);

	return result;
}

const fmat33 Mathematics::createScalingMatrix(const float x, const float y)
{
	fmat33 result = fmat33(1.0f);

	result.m[0][0] = x;
	result.m[1][1] = y;

	return result;
}

const float Mathematics::convertToRadians(const float angle)
{
	return (angle * DEG2RAD);
}

const float Mathematics::limitAngle(const float angle)
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

const float Mathematics::getSignum(float value)
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

const float Mathematics::getPi()
{
	return PI;
}