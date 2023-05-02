#pragma once

#include "tone.hpp"

class ToneManager final
{
public:
	void addTone(const shared_ptr<Tone> & tone);

private:
	vector<shared_ptr<Tone>> _tones = {};
};