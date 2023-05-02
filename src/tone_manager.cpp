#include "tone_manager.hpp"

void ToneManager::addTone(const shared_ptr<Tone> & tone)
{
	_tones.push_back(tone);
}