#pragma once

struct ivec2;

struct fvec2 final
{
	fvec2(const double value);
	fvec2(const double x, const double y);
	fvec2(const ivec2 & other);

	void operator+=(const fvec2 & other);

	const fvec2 operator+(const fvec2 & other) const;
	const fvec2 operator*(const fvec2 & other) const;

	double x;
	double y;
};