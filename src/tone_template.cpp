#include "tone_template.hpp"
#include "tone_constants.hpp"

ToneTemplate::ToneTemplate()
{
	for(int index = 0; index < ToneConstants::OCTAVE_COUNT; index++)
	{
		sineAmplitudes.push_back(0);
		squareAmplitudes.push_back(0);
		triangleAmplitudes.push_back(0);
		sawtoothAmplitudes.push_back(0);
		sineToggles.push_back(false);
		squareToggles.push_back(false);
		triangleToggles.push_back(false);
		sawtoothToggles.push_back(false);
	}
}