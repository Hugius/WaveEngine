#pragma once

#include "tone_template.hpp"

#include <memory>

using std::shared_ptr;

class Tone final
{
public:
	Tone(const shared_ptr<ToneTemplate> & toneTemplate);

	void setNoteIndex(const int value);
	void setDuration(const int value);

	const shared_ptr<ToneTemplate> & getToneTemplate() const;

	const int getNoteIndex() const;
	const int getDuration() const;

private:
	const shared_ptr<ToneTemplate> _toneTemplate;

	int _noteIndex = 0;
	int _duration = 0;
};