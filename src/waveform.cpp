#include "waveform.hpp"

Waveform::Waveform(const unsigned char * bytes, const int byteCount, const int channelCount, const int samplesPerSecond, const int bytesPerSecond, const int bytesPerBlock, const int bitsPerSample)
{
	if(bytes == nullptr)
	{
		abort();
	}

	if(byteCount < 1)
	{
		abort();
	}

	if(channelCount < 1)
	{
		abort();
	}

	if(samplesPerSecond < 1)
	{
		abort();
	}

	if(bytesPerSecond < 1)
	{
		abort();
	}

	if(bytesPerBlock < 1)
	{
		abort();
	}

	if(bitsPerSample < 1)
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

Waveform::~Waveform()
{
	delete[] _header->lpData;

	delete _format;
	delete _header;
}

const PWAVEFORMATEX Waveform::getFormat() const
{
	return _format;
}

const PWAVEHDR Waveform::getHeader() const
{
	return _header;
}