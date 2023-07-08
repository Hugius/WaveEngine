#pragma once

struct dvec2;

struct ivec2 final
{
	ivec2(const int value);
	ivec2(const int x, const int y);
	ivec2(const dvec2 & other);

	const ivec2 operator-(const ivec2 & other) const;
	const ivec2 operator/(const ivec2 & other) const;

	int x;
	int y;
};