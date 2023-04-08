#include "audio.hpp"

Audio::Audio(const unsigned char * bytes, const int byteCount, const int channelCount, const int samplesPerSecond, const int bytesPerSecond, const int bytesPerBlock, const int bitsPerSample)
{
	if(bytes == nullptr || byteCount < 1 || channelCount < 1 || samplesPerSecond < 1 || bytesPerSecond < 1 || bytesPerBlock < 1 || bitsPerSample < 1)
	{
		abort();
	}

	_header = new WAVEHDR();
	_header->lpData = const_cast<char *>(reinterpret_cast<const char *>(bytes));
	_header->dwBufferLength = byteCount;

	_format = new WAVEFORMATEX();
	_format->wFormatTag = WAVE_FORMAT_PCM;
	_format->nChannels = channelCount;
	_format->nSamplesPerSec = samplesPerSecond;
	_format->nAvgBytesPerSec = bytesPerSecond;
	_format->nBlockAlign = bytesPerBlock;
	_format->wBitsPerSample = bitsPerSample;
}

Audio::~Audio()
{
	delete[] _header->lpData;

	delete _format;
	delete _header;
}

const PWAVEFORMATEX Audio::getFormat() const
{
	return _format;
}

const PWAVEHDR Audio::getHeader() const
{
	return _header;
}