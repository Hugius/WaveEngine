#pragma once

struct ivec2;

struct dvec2 final
{
	dvec2(const double value);
	dvec2(const double x, const double y);
	dvec2(const ivec2 & other);

	void operator+=(const dvec2 & other);

	const dvec2 operator+(const dvec2 & other) const;
	const dvec2 operator*(const dvec2 & other) const;

	double x;
	double y;
};