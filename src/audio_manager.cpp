#include "audio_manager.hpp"

void AudioManager::addAudio(const string & id, const shared_ptr<Audio> & audio)
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

const unordered_map<string, shared_ptr<Audio>> & AudioManager::getAudios() const
{
	return _audios;
}

const bool AudioManager::_isAudioExisting(const string & id) const
{
	return _audios.find(id) != _audios.end();
}