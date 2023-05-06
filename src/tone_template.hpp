#pragma once

#include "shared_constants.hpp"

#include <array>

using std::array;

class ToneTemplate final
{
public:
	void setDuration(const int value);

	void setSineAmplitudes(const array<int, SharedConstants::OCTAVE_COUNT> & value);
	void setSquareAmplitudes(const array<int, SharedConstants::OCTAVE_COUNT> & value);
	void setTriangleAmplitudes(const array<int, SharedConstants::OCTAVE_COUNT> & value);
	void setSawtoothAmplitudes(const array<int, SharedConstants::OCTAVE_COUNT> & value);
	void setSineToggles(const array<bool, SharedConstants::OCTAVE_COUNT> & value);
	void setSquareToggles(const array<bool, SharedConstants::OCTAVE_COUNT> & value);
	void setTriangleToggles(const array<bool, SharedConstants::OCTAVE_COUNT> & value);
	void setSawtoothToggles(const array<bool, SharedConstants::OCTAVE_COUNT> & value);

	const array<int, SharedConstants::OCTAVE_COUNT> & getSineAmplitudes() const;
	const array<int, SharedConstants::OCTAVE_COUNT> & getSquareAmplitudes() const;
	const array<int, SharedConstants::OCTAVE_COUNT> & getTriangleAmplitudes() const;
	const array<int, SharedConstants::OCTAVE_COUNT> & getSawtoothAmplitudes() const;
	const array<bool, SharedConstants::OCTAVE_COUNT> & getSineToggles() const;
	const array<bool, SharedConstants::OCTAVE_COUNT> & getSquareToggles() const;
	const array<bool, SharedConstants::OCTAVE_COUNT> & getTriangleToggles() const;
	const array<bool, SharedConstants::OCTAVE_COUNT> & getSawtoothToggles() const;

	const int getDuration() const;

private:
	array<int, SharedConstants::OCTAVE_COUNT> _sineAmplitudes = {};
	array<int, SharedConstants::OCTAVE_COUNT> _squareAmplitudes = {};
	array<int, SharedConstants::OCTAVE_COUNT> _triangleAmplitudes = {};
	array<int, SharedConstants::OCTAVE_COUNT> _sawtoothAmplitudes = {};
	array<bool, SharedConstants::OCTAVE_COUNT> _sineToggles = {};
	array<bool, SharedConstants::OCTAVE_COUNT> _squareToggles = {};
	array<bool, SharedConstants::OCTAVE_COUNT> _triangleToggles = {};
	array<bool, SharedConstants::OCTAVE_COUNT> _sawtoothToggles = {};

	int _duration = 10;
};