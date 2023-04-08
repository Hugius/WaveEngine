#pragma once

#include <windows.h>

class Audio final
{
public:
	Audio(const unsigned char * bytes, const int byteCount, const int channelCount, const int samplesPerSecond, const int bytesPerSecond, const int bytesPerBlock, const int bitsPerSample);
	~Audio();

	const PWAVEHDR getHeader() const;
	const PWAVEFORMATEX getFormat() const;

private:
	PWAVEHDR _header = nullptr;
	PWAVEFORMATEX _format = nullptr;
};