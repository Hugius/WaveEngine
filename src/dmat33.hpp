#pragma once

#include "dvec2.hpp"

struct dmat33 final
{
	dmat33(const double value);

	const dmat33 operator*(const dmat33 & other) const;
	const dvec2 operator*(const dvec2 & other) const;

	union
	{
		double m[3][3];
		double f[9];
	};
};