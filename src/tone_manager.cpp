#include "tone_manager.hpp"

void ToneManager::addNewTone(const shared_ptr<Tone> & tone)
{
	_tones.push_back(tone);
}

void ToneManager::removeCurrentTone()
{
	if(_tones.empty())
	{
		abort();
	}

	_tones.erase(_tones.begin() + _currentToneIndex);

	if(_currentToneIndex == _tones.size())
	{
		_currentToneIndex--;
	}
}

void ToneManager::selectPreviousTone()
{
	if(_currentToneIndex == 0)
	{
		abort();
	}

	_currentToneIndex--;
}

void ToneManager::selectNextTone()
{
	if(_currentToneIndex == _tones.size() - 1)
	{
		abort();
	}

	_currentToneIndex++;
}

const shared_ptr<Tone> & ToneManager::getCurrentTone() const
{
	if(_tones.empty())
	{
		abort();
	}

	return _tones.at(_currentToneIndex);
}

const int ToneManager::getCurrentToneIndex() const
{
	return _currentToneIndex;
}

const int ToneManager::getToneCount() const
{
	return static_cast<int>(_tones.size());
}