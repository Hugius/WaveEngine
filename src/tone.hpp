#pragma once

#include "note_type.hpp"

#include <vector>

using std::vector;

struct Tone final
{
	Tone();

	vector<int> sineAmplitudes;
	vector<int> squareAmplitudes;
	vector<int> triangleAmplitudes;
	vector<int> sawtoothAmplitudes;
	vector<bool> sineToggles;
	vector<bool> squareToggles;
	vector<bool> triangleToggles;
	vector<bool> sawtoothToggles;

	int duration;

	NoteType note;
};