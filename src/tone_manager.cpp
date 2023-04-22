#include "tone_manager.hpp"

void ToneManager::addTone(const shared_ptr<Tone> & tone)
{
	_tones.push_back(tone);
}

void ToneManager::increaseCurrentIndex()
{
	if(_currentIndex < _tones.size() - 1)
	{
		_currentIndex++;
	}
}

void ToneManager::decreaseCurrentIndex()
{
	if(_currentIndex > 0)
	{
		_currentIndex--;
	}
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