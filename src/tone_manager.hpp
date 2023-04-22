#pragma once

#include "tone.hpp"

#include <memory>

using std::shared_ptr;

class ToneManager final
{
public:
	void addTone(const shared_ptr<Tone> & tone);
	void increaseCurrentIndex();
	void decreaseCurrentIndex();

	const shared_ptr<Tone> & getCurrentTone() const;
	const vector<shared_ptr<Tone>> & getTones() const;

	const int getCurrentIndex() const;

private:
	vector<shared_ptr<Tone>> _tones = {};

	int _currentIndex = 0;
};