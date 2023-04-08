#pragma once

#include "fvec2.hpp"

struct fmat33 final
{
	fmat33(const float value);

	const fmat33 operator*(const fmat33 & other) const;
	const fvec2 operator*(const fvec2 & other) const;

	union
	{
		float m[3][3];
		float f[9];
	};
};