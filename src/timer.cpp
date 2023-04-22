#include "timer.hpp"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;

void Timer::start()
{
	if(_isStarted)
	{
		abort();
	}

	_startEpoch = _getEpoch();
	_isStarted = true;
}

void Timer::stop()
{
	if(!_isStarted)
	{
		abort();
	}

	_stopEpoch = _getEpoch();
	_isStarted = false;
}

const double Timer::getDeltaTime() const
{
	if(_isStarted)
	{
		abort();
	}

	const long long difference = (_stopEpoch - _startEpoch);
	const double deltaTime = static_cast<double>(difference) / 1000000.0;

	return deltaTime;
}

const int Timer::getUpdateCountPerSecond() const
{
	return UPDATES_PER_SECOND;
}

const long long Timer::_getEpoch() const
{
	return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
}