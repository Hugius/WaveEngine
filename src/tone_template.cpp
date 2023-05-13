#include "tone_template.hpp"

void ToneTemplate::setDuration(const int value)
{
	if(value < Shared::MIN_TONE_DURATION)
	{
		abort();
	}

	if(value > Shared::MAX_TONE_DURATION)
	{
		abort();
	}

	if(value < _attack)
	{
		abort();
	}

	if(value < _release)
	{
		abort();
	}

	_duration = value;
}

void ToneTemplate::setRelease(const int value)
{
	if(value < 0)
	{
		abort();
	}

	if(value > _duration)
	{
		abort();
	}

	if(value < _attack)
	{
		abort();
	}

	_release = value;
}

void ToneTemplate::setSineAmplitudes(const array<int, Shared::OCTAVE_COUNT> & value)
{
	_sineAmplitudes = value;
}

void ToneTemplate::setSquareAmplitudes(const array<int, Shared::OCTAVE_COUNT> & value)
{
	_squareAmplitudes = value;
}

void ToneTemplate::setTriangleAmplitudes(const array<int, Shared::OCTAVE_COUNT> & value)
{
	_triangleAmplitudes = value;
}

void ToneTemplate::setSawtoothAmplitudes(const array<int, Shared::OCTAVE_COUNT> & value)
{
	_sawtoothAmplitudes = value;
}

void ToneTemplate::setSineToggles(const array<bool, Shared::OCTAVE_COUNT> & value)
{
	_sineToggles = value;
}

void ToneTemplate::setSquareToggles(const array<bool, Shared::OCTAVE_COUNT> & value)
{
	_squareToggles = value;
}

void ToneTemplate::setTriangleToggles(const array<bool, Shared::OCTAVE_COUNT> & value)
{
	_triangleToggles = value;
}

void ToneTemplate::setSawtoothToggles(const array<bool, Shared::OCTAVE_COUNT> & value)
{
	_sawtoothToggles = value;
}

void ToneTemplate::setAttack(const int value)
{
	if(value < 0)
	{
		abort();
	}

	if(value > _duration)
	{
		abort();
	}

	if(value > _release)
	{
		abort();
	}

	_attack = value;
}

const array<int, Shared::OCTAVE_COUNT> & ToneTemplate::getSineAmplitudes() const
{
	return _sineAmplitudes;
}

const array<int, Shared::OCTAVE_COUNT> & ToneTemplate::getSquareAmplitudes() const
{
	return _squareAmplitudes;
}

const array<int, Shared::OCTAVE_COUNT> & ToneTemplate::getTriangleAmplitudes() const
{
	return _triangleAmplitudes;
}

const array<int, Shared::OCTAVE_COUNT> & ToneTemplate::getSawtoothAmplitudes() const
{
	return _sawtoothAmplitudes;
}

const array<bool, Shared::OCTAVE_COUNT> & ToneTemplate::getSineToggles() const
{
	return _sineToggles;
}

const array<bool, Shared::OCTAVE_COUNT> & ToneTemplate::getSquareToggles() const
{
	return _squareToggles;
}

const array<bool, Shared::OCTAVE_COUNT> & ToneTemplate::getTriangleToggles() const
{
	return _triangleToggles;
}

const array<bool, Shared::OCTAVE_COUNT> & ToneTemplate::getSawtoothToggles() const
{
	return _sawtoothToggles;
}

const int ToneTemplate::getAttack() const
{
	return _attack;
}

const int ToneTemplate::getDuration() const
{
	return _duration;
}

const int ToneTemplate::getRelease() const
{
	return _release;
}