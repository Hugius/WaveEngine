#pragma once

struct fvec2;

struct ivec2 final
{
	ivec2(const int value);
	ivec2(const int x, const int y);
	ivec2(const fvec2 & other);

	int x;
	int y;
};