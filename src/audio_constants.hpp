#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

struct AudioConstants final
{
	static inline const vector<string> NOTE_NAMES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	static inline const vector<float> NOTE_FREQUENCIES = {261.63f, 277.18f, 293.66f, 311.13f, 329.63f, 349.23f, 369.99f, 392.00f, 415.30f, 440.00f, 466.16f, 493.88f};

	static inline const int MIN_DURATION = 0;
	static inline const int MAX_DURATION = 30000;
	static inline const int MIN_AMPLITUDE = 0;
	static inline const int MAX_AMPLITUDE = 30000;
	static inline const int MIN_FREQUENCY = 20;
	static inline const int MAX_FREQUENCY = 20000;
};