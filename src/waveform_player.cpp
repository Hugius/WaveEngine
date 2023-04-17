#include "waveform_player.hpp"

using std::make_shared;

void WaveformPlayer::start(const shared_ptr<Waveform> & waveform)
{
	if(isStarted())
	{
		abort();
	}

	const MMRESULT openResult = waveOutOpen(&_handle, WAVE_MAPPER, waveform->getFormat(), 0, 0, CALLBACK_NULL);

	if(openResult != MMSYSERR_NOERROR)
	{
		abort();
	}

	const int bufferLength = static_cast<int>(waveform->getHeader()->dwBufferLength);

	_header = new WAVEHDR();
	_header->lpData = new char[bufferLength];
	_header->dwBufferLength = bufferLength;

	for(int index = 0; index < bufferLength; index++)
	{
		_header->lpData[index] = waveform->getHeader()->lpData[index];
	}

	const MMRESULT prepareResult = waveOutPrepareHeader(_handle, _header, sizeof(WAVEHDR));

	if(prepareResult != MMSYSERR_NOERROR)
	{
		abort();
	}

	const MMRESULT writeResult = waveOutWrite(_handle, _header, sizeof(WAVEHDR));

	if(writeResult != MMSYSERR_NOERROR)
	{
		abort();
	}
}

void WaveformPlayer::stop()
{
	if(!isStarted())
	{
		abort();
	}

	waveOutReset(_handle);
	waveOutUnprepareHeader(_handle, _header, sizeof(WAVEHDR));
	waveOutClose(_handle);

	_handle = nullptr;
	_header = nullptr;
}

const bool WaveformPlayer::isStarted() const
{
	return _handle != nullptr;
}