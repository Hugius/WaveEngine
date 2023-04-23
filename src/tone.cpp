#include "tone.hpp"
#include "tone_constants.hpp"

Tone::Tone()
{
	for(int octaveIndex = 0; octaveIndex < ToneConstants::MAX_OCTAVE + 1; octaveIndex++)
	{
		sineAmplitudes.insert({octaveIndex, {}});
		squareAmplitudes.insert({octaveIndex, {}});
		triangleAmplitudes.insert({octaveIndex, {}});
		sawtoothAmplitudes.insert({octaveIndex, {}});
		sineToggles.insert({octaveIndex, {}});
		squareToggles.insert({octaveIndex, {}});
		triangleToggles.insert({octaveIndex, {}});
		sawtoothToggles.insert({octaveIndex, {}});

		for(int noteIndex = 0; noteIndex < ToneConstants::NOTE_COUNT; noteIndex++)
		{
			sineAmplitudes.at(octaveIndex).push_back(0);
			squareAmplitudes.at(octaveIndex).push_back(0);
			triangleAmplitudes.at(octaveIndex).push_back(0);
			sawtoothAmplitudes.at(octaveIndex).push_back(0);
			sineToggles.at(octaveIndex).push_back(false);
			squareToggles.at(octaveIndex).push_back(false);
			triangleToggles.at(octaveIndex).push_back(false);
			sawtoothToggles.at(octaveIndex).push_back(false);
		}
	}
}