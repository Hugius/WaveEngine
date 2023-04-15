#pragma once

#include "audio.hpp"
#include "waveform_type.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class WaveformGenerator final
{
public:
	const shared_ptr<Audio> generateSineWaveform(const int duration, const double amplitude, const double frequency) const;
	const shared_ptr<Audio> generateSquareWaveform(const int duration, const double amplitude, const double frequency) const;
	const shared_ptr<Audio> generateTriangleWaveform(const int duration, const double amplitude, const double frequency) const;
	const shared_ptr<Audio> generateSawtoothWaveform(const int duration, const double amplitude, const double frequency) const;
	const shared_ptr<Audio> combineWaveforms(const vector<shared_ptr<Audio>> & waveforms) const;
	const vector<double> extractSamplesFromWaveform(const shared_ptr<Audio> & waveform);

private:
	const shared_ptr<Audio> _generateWaveform(const int duration, const double amplitude, const double frequency, const WaveformType type) const;

	static inline const int CHANNEL_COUNT = 2;
	static inline const int SAMPLES_PER_SECOND = 44100;
	static inline const int BYTES_PER_SECOND = 176400;
	static inline const int BYTES_PER_BLOCK = 4;
	static inline const int BITS_PER_SAMPLE = 16;
};