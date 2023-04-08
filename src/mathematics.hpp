#pragma once

#include "fmat33.hpp"

#include <vector>

using std::vector;

class Mathematics final
{
public:
	Mathematics() = delete;

	static const vector<float> calculateDistributedPositions(const float start, const float range, const int count);

	static const fmat33 createTranslationMatrix(const float x, const float y);
	static const fmat33 createRotationMatrix(const float angle);
	static const fmat33 createScalingMatrix(const float x, const float y);

	static const double convertToRadians(const double degrees);
	static const double limitAngle(const double angle);
	static const double getSignum(double value);
	static const double getPi();

private:
	static inline const double DEG2RAD = 0.01745329251994329576;
	static inline const double PI = 3.14159265358979323846;
};