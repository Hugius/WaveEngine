#include "waveform_player.hpp"

using std::make_shared;

void WaveformPlayer::start(const shared_ptr<Waveform> & waveform, bool isLooped)
{
	if(waveform == nullptr)
	{
		abort();
	}

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

	if(isLooped)
	{
		_header->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		_header->dwLoops = -1;
	}

	for(int index = 0; index < bufferLength; index++)
	{
		_header->lpData[index] = waveform->getHeader()->lpData[index];
	}

	const MMRESULT prepareHeaderResult = waveOutPrepareHeader(_handle, _header, sizeof(WAVEHDR));

	if(prepareHeaderResult != MMSYSERR_NOERROR)
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

	const MMRESULT resetResult = waveOutReset(_handle);

	if(resetResult != MMSYSERR_NOERROR)
	{
		abort();
	}

	const MMRESULT unprepareHeaderResult = waveOutUnprepareHeader(_handle, _header, sizeof(WAVEHDR));

	if(unprepareHeaderResult != MMSYSERR_NOERROR)
	{
		abort();
	}

	const MMRESULT closeResult = waveOutClose(_handle);

	if(closeResult != MMSYSERR_NOERROR)
	{
		abort();
	}

	_handle = nullptr;
	_header = nullptr;
}

void WaveformPlayer::update()
{
	if(isStarted())
	{
		if(_header->dwFlags == (WHDR_PREPARED | WHDR_DONE))
		{
			stop();
		}
	}
}

const bool WaveformPlayer::isStarted() const
{
	return _handle != nullptr;
}