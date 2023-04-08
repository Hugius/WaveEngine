#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

struct AudioConstants final
{
	static inline const vector<string> NOTE_NAMES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	static inline const vector<float> NOTE_FREQUENCIES = {261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88f};

	static inline const int MIN_DURATION = 0;
	static inline const int MAX_DURATION = 30000;
	static inline const int MIN_AMPLITUDE = 0;
	static inline const int MAX_AMPLITUDE = 30000;
	static inline const int MIN_FREQUENCY = 20;
	static inline const int MAX_FREQUENCY = 20000;
};