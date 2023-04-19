#include "tone_manager.hpp"

void ToneManager::addTone(const string & id, const shared_ptr<Tone> & tone)
{
	if(_isToneExisting(id))
	{
		abort();
	}

	_tones.insert({id, tone});
}

const shared_ptr<Tone> & ToneManager::getTone(const string & id) const
{
	if(!_isToneExisting(id))
	{
		abort();
	}

	return _tones.at(id);
}

const unordered_map<string, shared_ptr<Tone>> & ToneManager::getTones() const
{
	return _tones;
}

const bool ToneManager::_isToneExisting(const string & id) const
{
	return _tones.find(id) != _tones.end();
}