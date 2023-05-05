#include "tone.hpp"
#include "tone_constants.hpp"

Tone::Tone(const shared_ptr<ToneTemplate> & toneTemplate)
	:
	_toneTemplate(toneTemplate)
{
	if(toneTemplate == nullptr)
	{
		abort();
	}
}

void Tone::setNoteIndex(const int value)
{
	if(value < 0)
	{
		abort();
	}

	if(value > ToneConstants::NOTE_COUNT - 1)
	{
		abort();
	}

	_noteIndex = value;
}

const shared_ptr<ToneTemplate> & Tone::getToneTemplate() const
{
	return _toneTemplate;
}

const int Tone::getNoteIndex() const
{
	return _noteIndex;
}