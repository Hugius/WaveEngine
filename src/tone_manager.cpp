#include "tone_manager.hpp"

void ToneManager::addTone(const shared_ptr<Tone> & tone)
{
	_tones.push_back(tone);
}

const shared_ptr<Tone> & ToneManager::getTone(const int index) const
{
	if(index < 0)
	{
		abort();
	}

	if(index >= _tones.size())
	{
		abort();
	}

	return _tones.at(index);
}

const vector<shared_ptr<Tone>> & ToneManager::getTones() const
{
	return _tones;
}

const int ToneManager::getCurrentIndex() const
{
	return _currentIndex;
}