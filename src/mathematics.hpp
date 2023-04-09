#pragma once

#include "dmat33.hpp"

#include <vector>

using std::vector;

class Mathematics final
{
public:
	Mathematics() = delete;

	static const vector<double> calculateDistributedPositions(const double start, const double range, const int count);

	static const dmat33 createTranslationMatrix(const double x, const double y);
	static const dmat33 createRotationMatrix(const double angle);
	static const dmat33 createScalingMatrix(const double x, const double y);

	static const double convertToRadians(const double degrees);
	static const double limitAngle(const double angle);
	static const double getSignum(const double value);
	static const double getPi();

private:
	static inline const double DEG2RAD = 0.017453292519943;
	static inline const double PI = 3.141592653589793;
};