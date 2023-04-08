#pragma once

#include "audio.hpp"

#include <memory>

using std::shared_ptr;

class AudioPlayer final
{
public:
	void start(shared_ptr<Audio> audio);
	void stop();
	void update();

	const bool isStarted() const;

private:
	HWAVEOUT _handle = nullptr;
	LPWAVEHDR _header = nullptr;
};