#pragma once

struct ivec2;

struct fvec2 final
{
	fvec2(const float value);
	fvec2(const float x, const float y);
	fvec2(const ivec2 & other);

	void operator+=(const fvec2 & other);

	const fvec2 operator+(const fvec2 & other) const;
	const fvec2 operator*(const fvec2 & other) const;

	float x;
	float y;
};