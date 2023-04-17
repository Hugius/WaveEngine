#pragma once

#include "waveform.hpp"

#include <memory>

using std::shared_ptr;

class WaveformPlayer final
{
public:
	void start(const shared_ptr<Waveform> & waveform);
	void stop();

	const bool isStarted() const;

private:
	HWAVEOUT _handle = nullptr;
	LPWAVEHDR _header = nullptr;
};