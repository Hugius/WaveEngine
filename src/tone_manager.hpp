#pragma once

#include "tone.hpp"

#include <vector>

using std::vector;

class ToneManager final
{
public:
	void addTone(const shared_ptr<Tone> & tone);

private:
	vector<shared_ptr<Tone>> _tones = {};
};