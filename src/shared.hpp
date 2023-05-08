#pragma once

#include "dvec3.hpp"

struct Shared final
{
	static inline const dvec3 WHITE = dvec3(1.0);
	static inline const dvec3 BLACK = dvec3(0.0);

	static inline const int OCTAVE_COUNT = 10;
	static inline const int NOTE_COUNT = 12;
	static inline const int MIN_TONE_ATTACK = 0;
	static inline const int MAX_TONE_ATTACK = 500;
	static inline const int MIN_TONE_DURATION = 10;
	static inline const int MAX_TONE_DURATION = 500;
	static inline const int MIN_TONE_RELEASE = 0;
	static inline const int MAX_TONE_RELEASE = 500;
	static inline const int MAX_TONE_TEMPLATES = 99;
};