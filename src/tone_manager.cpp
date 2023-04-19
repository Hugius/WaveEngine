#include "tone_manager.hpp"

void ToneManager::addTone(const shared_ptr<Tone> & tone)
{
	_tones.push_back(tone);
}

const shared_ptr<Tone> & ToneManager::getCurrentTone() const
{
	if(_tones.empty())
	{
		abort();
	}

	return _tones.at(_currentIndex);
}

const vector<shared_ptr<Tone>> & ToneManager::getTones() const
{
	return _tones;
}

const int ToneManager::getCurrentIndex() const
{
	return _currentIndex;
}