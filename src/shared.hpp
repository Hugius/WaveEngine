#pragma once

#include "dvec3.hpp"

struct Shared final
{
	static inline const int OCTAVE_COUNT = 10;
	static inline const int NOTE_COUNT = 12;
	static inline const int MIN_TONE_DURATION = 10;
	static inline const int MAX_TONE_DURATION = 500;
	static inline const int MAX_TONE_TEMPLATES = 99;
};