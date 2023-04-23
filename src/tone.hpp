#pragma once

#include <vector>
#include <map>

using std::vector;
using std::map;

struct Tone final
{
	Tone();

	map<int, vector<int>> sineAmplitudes;
	map<int, vector<int>> squareAmplitudes;
	map<int, vector<int>> triangleAmplitudes;
	map<int, vector<int>> sawtoothAmplitudes;
	map<int, vector<bool>> sineToggles;
	map<int, vector<bool>> squareToggles;
	map<int, vector<bool>> triangleToggles;
	map<int, vector<bool>> sawtoothToggles;
};