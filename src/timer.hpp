#pragma once

#include <memory>

class Timer final
{
public:
	void start();
	void stop();

	const double getDeltaTime() const;

	const int getUpdateCountPerSecond() const;

private:
	const long long _getEpoch() const;

	static inline const int UPDATES_PER_SECOND = 75;

	long long _startEpoch = 0;
	long long _stopEpoch = 0;

	bool _isStarted = false;
};