#pragma once

#include "shared.hpp"

#include <array>

using std::array;

class ToneTemplate final
{
public:
	void setSineAmplitudes(const array<int, Shared::OCTAVE_COUNT> & value);
	void setSquareAmplitudes(const array<int, Shared::OCTAVE_COUNT> & value);
	void setTriangleAmplitudes(const array<int, Shared::OCTAVE_COUNT> & value);
	void setSawtoothAmplitudes(const array<int, Shared::OCTAVE_COUNT> & value);
	void setSineToggles(const array<bool, Shared::OCTAVE_COUNT> & value);
	void setSquareToggles(const array<bool, Shared::OCTAVE_COUNT> & value);
	void setTriangleToggles(const array<bool, Shared::OCTAVE_COUNT> & value);
	void setSawtoothToggles(const array<bool, Shared::OCTAVE_COUNT> & value);
	void setAttack(const int value);
	void setDuration(const int value);
	void setRelease(const int value);

	const array<int, Shared::OCTAVE_COUNT> & getSineAmplitudes() const;
	const array<int, Shared::OCTAVE_COUNT> & getSquareAmplitudes() const;
	const array<int, Shared::OCTAVE_COUNT> & getTriangleAmplitudes() const;
	const array<int, Shared::OCTAVE_COUNT> & getSawtoothAmplitudes() const;
	const array<bool, Shared::OCTAVE_COUNT> & getSineToggles() const;
	const array<bool, Shared::OCTAVE_COUNT> & getSquareToggles() const;
	const array<bool, Shared::OCTAVE_COUNT> & getTriangleToggles() const;
	const array<bool, Shared::OCTAVE_COUNT> & getSawtoothToggles() const;

	const int getAttack() const;
	const int getDuration() const;
	const int getRelease() const;

private:
	array<int, Shared::OCTAVE_COUNT> _sineAmplitudes = {};
	array<int, Shared::OCTAVE_COUNT> _squareAmplitudes = {};
	array<int, Shared::OCTAVE_COUNT> _triangleAmplitudes = {};
	array<int, Shared::OCTAVE_COUNT> _sawtoothAmplitudes = {};
	array<bool, Shared::OCTAVE_COUNT> _sineToggles = {};
	array<bool, Shared::OCTAVE_COUNT> _squareToggles = {};
	array<bool, Shared::OCTAVE_COUNT> _triangleToggles = {};
	array<bool, Shared::OCTAVE_COUNT> _sawtoothToggles = {};

	int _attack = 0;
	int _duration = Shared::MIN_TONE_DURATION;
	int _release = 0;
};