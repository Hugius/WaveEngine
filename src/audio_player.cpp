#include "audio_player.hpp"

using std::make_shared;

void AudioPlayer::start(shared_ptr<Audio> audio)
{
	if(isStarted())
	{
		abort();
	}

	const MMRESULT openResult = waveOutOpen(&_handle, WAVE_MAPPER, audio->getFormat(), 0, 0, CALLBACK_NULL);

	if(openResult != MMSYSERR_NOERROR)
	{
		abort();
	}

	const int bufferLength = static_cast<int>(audio->getHeader()->dwBufferLength);

	_header = new WAVEHDR();
	_header->lpData = new char[bufferLength];
	_header->dwBufferLength = bufferLength;

	for(int index = 0; index < bufferLength; index++)
	{
		_header->lpData[index] = audio->getHeader()->lpData[index];
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

void AudioPlayer::stop()
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

void AudioPlayer::update()
{
	//if(isStarted() && _header->dwFlags == (WHDR_PREPARED | WHDR_DONE))
	//{
	//	_header->dwFlags = WHDR_PREPARED;

	//	const auto writeResult = waveOutWrite(_handle, _header, sizeof(WAVEHDR));

	//	if(writeResult != MMSYSERR_NOERROR)
	//	{
	//		abort();
	//	}
	//}
}

const bool AudioPlayer::isStarted() const
{
	return _handle != nullptr;
}