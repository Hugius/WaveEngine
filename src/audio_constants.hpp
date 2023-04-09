#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

struct AudioConstants final
{
	static inline const vector<string> NOTE_NAMES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	static inline const vector<double> NOTE_FREQUENCIES = {16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87};

	static inline const int MIN_DURATION = 0;
	static inline const int MAX_DURATION = 30000;
	static inline const int MIN_AMPLITUDE = 0;
	static inline const int MAX_AMPLITUDE = 30000;
	static inline const int MIN_FREQUENCY = 20;
	static inline const int MAX_FREQUENCY = 20000;
};