#pragma once

#include <vector>

using std::vector;

struct ToneTemplate final
{
	ToneTemplate();

	vector<int> sineAmplitudes;
	vector<int> squareAmplitudes;
	vector<int> triangleAmplitudes;
	vector<int> sawtoothAmplitudes;
	vector<bool> sineToggles;
	vector<bool> squareToggles;
	vector<bool> triangleToggles;
	vector<bool> sawtoothToggles;
};