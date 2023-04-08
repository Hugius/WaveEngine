#pragma once

#include "dvec2.hpp"

struct fmat33 final
{
	fmat33(const double value);

	const fmat33 operator*(const fmat33 & other) const;
	const fvec2 operator*(const fvec2 & other) const;

	union
	{
		double m[3][3];
		double f[9];
	};
};