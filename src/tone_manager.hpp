#pragma once

#include "tone.hpp"

#include <memory>

using std::shared_ptr;

class ToneManager final
{
public:
	void addNewTone(const shared_ptr<Tone> & tone);
	void removeCurrentTone();
	void selectPreviousTone();
	void selectNextTone();

	const shared_ptr<Tone> & getCurrentTone() const;

	const int getCurrentToneIndex() const;
	const int getToneCount() const;

private:
	vector<shared_ptr<Tone>> _tones = {};

	int _currentToneIndex = 0;
};