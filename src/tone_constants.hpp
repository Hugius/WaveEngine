#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

struct ToneConstants final
{
	static inline const vector<string> NOTE_NAMES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	static inline const vector<double> NOTE_FREQUENCIES = {16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87};

	static inline const double OCTAVE_AMPLITUDE_STEP = 1000.0;

	static inline const int MIN_OCTAVE = 0;
	static inline const int MAX_OCTAVE = 9;
	static inline const int DEFAULT_OCTAVE = 4;
	static inline const int OCTAVE_COUNT = 10;
	static inline const int NOTE_COUNT = 12;
};