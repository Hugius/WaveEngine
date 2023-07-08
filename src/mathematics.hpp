#pragma once

#include "dmat33.hpp"

#include <vector>

using std::vector;

class Mathematics final
{
public:
	Mathematics() = delete;

	static const vector<double> calculateDistributedPositions(const double start, const double range, const int count, const bool mustIncludeFirst, const bool mustIncludeLast);

	static const dmat33 createTranslationMatrix(const double x, const double y);
	static const dmat33 createScalingMatrix(const double x, const double y);

	static const double getSignum(const double number);
	static const double getPi();

private:
	static inline const double PI = 3.141592653589793;
};