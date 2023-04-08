#include "audio_player.hpp"

using std::make_shared;

void AudioPlayer::start(shared_ptr<Audio> audio)
{
	HWAVEOUT handle = nullptr;

	const MMRESULT openResult = waveOutOpen(&handle, WAVE_MAPPER, audio->getFormat(), 0, 0, CALLBACK_NULL);

	if(openResult != MMSYSERR_NOERROR)
	{
		if(openResult == MMSYSERR_BADDEVICEID)
		{
			return;
		}
		else
		{
			abort();
		}
	}

	const LPWAVEHDR header = new WAVEHDR();

	header->dwBufferLength = audio->getHeader()->dwBufferLength;
	header->lpData = new char[header->dwBufferLength];
	header->dwFlags = 0;

	for(int index = 0; index < static_cast<int>(header->dwBufferLength); index++)
	{
		header->lpData[index] = audio->getHeader()->lpData[index];
	}

	const MMRESULT prepareResult = waveOutPrepareHeader(handle, header, sizeof(WAVEHDR));

	if(prepareResult != MMSYSERR_NOERROR)
	{
		if(prepareResult == MMSYSERR_NODRIVER)
		{
			return;
		}
		else
		{
			abort();
		}
	}

	const MMRESULT writeResult = waveOutWrite(handle, header, sizeof(WAVEHDR));

	if(writeResult != MMSYSERR_NOERROR)
	{
		if(writeResult == MMSYSERR_NODRIVER)
		{
			return;
		}
		else if(writeResult == MMSYSERR_NOMEM)
		{
			const MMRESULT unprepareResult = waveOutUnprepareHeader(handle, header, sizeof(WAVEHDR));

			if(unprepareResult != MMSYSERR_NOERROR)
			{
				if(unprepareResult == MMSYSERR_NODRIVER)
				{
					return;
				}
				else
				{

					abort();
				}
			}

			const MMRESULT closeResult = waveOutClose(handle);

			if(closeResult != MMSYSERR_NOERROR)
			{
				if(closeResult == MMSYSERR_NODRIVER)
				{
					return;
				}
				else
				{
					abort();
				}
			}

			return;
		}
		else
		{
			abort();
		}
	}
}

void AudioPlayer::stop(shared_ptr<Audio> audio)
{
	waveOutReset(audio->getHandle());
}