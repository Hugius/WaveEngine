#include "timer.hpp"

#include <chrono>

using std::make_unique;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;

Timer::Timer()
	:
	_clock(make_unique<Clock>())
{

}

void Timer::start()
{
	if(_clock->isStarted)
	{
		abort();
	}

	_clock->startEpoch = _getEpoch();
	_clock->isStarted = true;
}

void Timer::stop()
{
	if(!_clock->isStarted)
	{
		abort();
	}

	_clock->stopEpoch = _getEpoch();
	_clock->isStarted = false;
}

const double Timer::getDeltaTime() const
{
	if(_clock->isStarted)
	{
		abort();
	}

	const long long difference = (_clock->stopEpoch - _clock->startEpoch);
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