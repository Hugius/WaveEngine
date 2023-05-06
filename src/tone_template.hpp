#pragma once

#include "tone_constants.hpp"

#include <array>

using std::array;

struct ToneTemplate final
{
	array<int, ToneConstants::OCTAVE_COUNT> sineAmplitudes = {};
	array<int, ToneConstants::OCTAVE_COUNT> squareAmplitudes = {};
	array<int, ToneConstants::OCTAVE_COUNT> triangleAmplitudes = {};
	array<int, ToneConstants::OCTAVE_COUNT> sawtoothAmplitudes = {};
	array<bool, ToneConstants::OCTAVE_COUNT> sineToggles = {};
	array<bool, ToneConstants::OCTAVE_COUNT> squareToggles = {};
	array<bool, ToneConstants::OCTAVE_COUNT> triangleToggles = {};
	array<bool, ToneConstants::OCTAVE_COUNT> sawtoothToggles = {};

	int duration = 10;
};