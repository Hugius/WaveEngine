#include "tone_manager.hpp"

void ToneManager::addTone(const shared_ptr<Tone> & tone)
{
	if(tone == nullptr)
	{
		abort();
	}

	_tones.push_back(tone);
}