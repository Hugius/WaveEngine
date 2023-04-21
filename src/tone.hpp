#pragma once

#include <vector>

using std::vector;

struct Tone final
{
	Tone();

	vector<int> sineAmplitudes;
	vector<int> squareAmplitudes;
	vector<int> triangleAmplitudes;
	vector<int> sawtoothAmplitudes;

	int octave;

	bool isSineEnabled;
	bool isSquareEnabled;
	bool isTriangleEnabled;
	bool isSawtoothEnabled;
};