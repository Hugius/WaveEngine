#pragma once

#include "tone.hpp"

#include <memory>

using std::shared_ptr;

class ToneManager final
{
public:
	void addTone(const shared_ptr<Tone> & tone);

	const shared_ptr<Tone> & getTone(const int index) const;
	const vector<shared_ptr<Tone>> & getTones() const;

private:
	vector<shared_ptr<Tone>> _tones = {};
};