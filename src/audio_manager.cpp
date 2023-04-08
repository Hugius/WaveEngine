#include "audio_manager.hpp"

void AudioManager::createAudio(const string & id, shared_ptr<Audio> audio)
{
	if(_isAudioExisting(id))
	{
		abort();
	}

	_audios.insert({id, audio});
}

const shared_ptr<Audio> & AudioManager::getAudio(const string & id) const
{
	if(!_isAudioExisting(id))
	{
		abort();
	}

	return _audios.at(id);
}

const bool AudioManager::_isAudioExisting(const string & id) const
{
	return _audios.find(id) != _audios.end();
}