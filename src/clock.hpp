#pragma once

struct Clock final
{
	Clock();

	long long startEpoch;
	long long stopEpoch;

	bool isStarted;
};