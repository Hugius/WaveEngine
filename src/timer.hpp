#pragma once

#include "clock.hpp"

#include <memory>

using std::unique_ptr;

class Timer final
{
public:
	void initialize();
	void start();
	void stop();

	const float getDeltaTime() const;

	const int getUpdateCountPerSecond() const;

private:
	const long long _getEpoch() const;

	static inline const int UPDATES_PER_SECOND = 75;

	unique_ptr<Clock> _clock = nullptr;
};