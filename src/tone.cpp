#include "tone.hpp"
#include "tone_constants.hpp"

Tone::Tone()
	:
	octave(ToneConstants::DEFAULT_OCTAVE),
	isSineEnabled(false),
	isSquareEnabled(false),
	isTriangleEnabled(false),
	isSawtoothEnabled(false)
{
	for(int index = 0; index < static_cast<int>(ToneConstants::NOTE_NAMES.size()); index++)
	{
		sineAmplitudes.push_back(0);
		squareAmplitudes.push_back(0);
		triangleAmplitudes.push_back(0);
		sawtoothAmplitudes.push_back(0);
	}
}